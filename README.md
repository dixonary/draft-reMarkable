[![rm1](https://img.shields.io/badge/rM1-supported-green)](https://remarkable.com/store/remarkable)
[![rm2](https://img.shields.io/badge/rM2-unsupported-red)](https://remarkable.com/store/remarkable-2)
[![opkg](https://img.shields.io/badge/OPKG-draft-blue)](https://github.com/matteodelabre/toltec)
[![Discord](https://img.shields.io/discord/463752820026376202.svg?label=reMarkable&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/ATqQGfu)

# draft-reMarkable
A launcher for the reMarkable tablet, which wraps around the standard interface.

[Draft v0.2 video](https://www.youtube.com/watch?v=VEngMK54SV4)

- [QT Creator Set-up](#qt-creator-set-up)
  * [1. Setup QT Creator](#1-setup-qt-creator)
  * [2. Deploy draft](#2-deploy-draft)
    + [2.i (optional) Deploy button-capture](#2i--optional--deploy-button-capture)
    + [2.ii (optional) Deploy fingerterm](#2ii--optional--deploy-fingerterm)
  * [3. Enable at startup](#3-enable-at-startup)
  * [4. Restart your reMarkable](#4-restart-your-remarkable)
- [Build setup without QT Creator](#build-setup-without-qt-creator)
  * [1. Download and install source and toolchain](#1-download-and-install-source-and-toolchain)
  * [2. Run build script](#2-run-build-script)
  * [3. Deploy](#3-deploy)
- [Configuration Files](#configuration-files)

* * *

## QT Creator Set-up

This information is quite vague. Reddit user /u/prpletentacle wrote up their process for setting up Draft+rM, with the Plato app, here: https://www.reddit.com/r/RemarkableTablet/comments/bkbps9/how_to_install_plato_reader_and_add_it_to_draft/?st=jvp0mqus&sh=0651e353

(nb. You fiddle with the internal system of your reMarkable at your own risk! Here be dragons.)

### 1. Setup QT Creator
To build draft you'll need to first set up QT Creator, which is covered on the [reMarkable wiki](https://remarkablewiki.com/devel/qt_creator).

### 2. Deploy draft
This should simply be a case of opening up qtcreator, loading up the project with the normal reMarkable target, and hitting "run".

As well as deploying the program, this will also populate `/etc/draft` with some sample commands and add a `/lib/systemd/system/draft.service` systemd file.


#### 2.i (optional) Deploy button-capture

[This small program](https://github.com/dixonary/button-capture-reMarkable) allows you to close the current application and return to the draft launcher. There is no native way to close `xochitl` so this is a very useful thing to have if you want to switch between applications. 


#### 2.ii (optional) Deploy fingerterm

[This terminal](https://github.com/dixonary/fingerterm-reMarkable) runs on the reMarkable and lets you change some config things without needing to SSH in! It's one of the default config options but you can remove that if you are't wanting to use it.

### 3. Enable at startup
You need to replace the normal xochitl startup with draft. This is done with the following two lines via SSH:

```bash
systemctl disable xochitl
systemctl enable draft
```

### 4. Restart your reMarkable

On restart you should find that `xochitl`, `fingerterm` and `shutdown` are your available choices and the draft launcher is running.


* * * 

## Build setup without QT Creator

These steps should help you automate a build setup. This way:
* You can build draft with a script (and without needing a GUI)
* You can build the software without needing the device plugged in/can package and deploy however you want
* You can leverage the cross compiler to build whatever software you want (see sidenote in step 3 below)

Note: NixOS has a package called [remarkable-toolchain](https://github.com/NixOS/nixpkgs/tree/master/pkgs/development/tools/misc/remarkable/remarkable-toolchain) in the unstable channel (aka not in 20.03 stock) that lets you skip the first step (although it doesn't give you a .nix-shell and you need to know where to find the files for step 2).

### 1. Download and install source and toolchain

```
$ git clone https://github.com/dixonary/draft-reMarkable
$ cd draft-reMarkable
# (ensure prereqs exist before installing toolchain: python, libarchive, file)
$ mkdir rm-toolchain
$ wget https://remarkable.engineering/oecore-x86_64-cortexa9hf-neon-toolchain-zero-gravitas-1.8-23.9.2019.sh
$ ./install-toolchain -D -y -d rm-toolchain
```
`-D` turns on set -x for the script (bash print debugging); `-y` says yes to everything; `-d` tells it where to install.
This file is a shell script with an embedded tar archive.  The script unpacks the archive and then edits shell scripts to contain the correct paths based on where you've installed it.

The installed toolchain then contains a [sysroot](https://doc.qt.io/qt-5/configure-linux-device.html), a package of binaries for cross compiling and some compiler/qt related environment variables setup by some shell scripts. There's probably plenty of redundant stuff here too.

### 2. Run build script

```
$ ./build.sh
```

For information on how this works, or how to use the cross-compiler for other binaries, see INSTALL.md.

### 3. Deploy
Run the install script with your reMarkable's IP address ([more details here](https://remarkablewiki.com/tech/ssh)).
```
$ ./draft-rm-install 172.17.0.3
```

You will be prompted for confirmation on downloading and installing and possibly for your device's root password. (You can preempt the prompts by calling the script with `-y`.) After installation draft should start automatically. You're set! You can view debug logs for draft and any app that draft tries to launch by running `journalctl -fu draft`.

To remove, you can run the `draft-rm-uninstall` script in the same way.

* * * 
## Configuration Files

Draft is configured through the files in the `/etc/draft` directory. They consist of a few simple lines. All of them are needed otherwise the option will not show up in the launcher.

`name`: Big word, left hand side of the screen.

`desc`: Smaller words, left hand side of the screen.

`call`: The shell command to run when the option is pressed.

`term`: The shell command to run while the option is running, to close it. (or it can do whatever you want really!) This won't do anything without `button-capture` installed.

`imgFile`: An icon to use. It will look for a PNG image with that name in the `/etc/draft/icons` directory.

*NOTE: Be sure not to leave any spaces around the "=" sign in the config lines, else the files may not parse correctly and your options may not show up!*
