## Manual build setup without QT Creator

Steps to build and install without using scripts

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


### 2. Activate environment

The installed toolchain contains a [sysroot](https://doc.qt.io/qt-5/configure-linux-device.html), a package of binaries for cross compiling and some compiler/qt related environment variables setup by some shell scripts. There's probably plenty of redundant stuff here too.

Activate:

```
$ . rm-toolchain/environment-setup-cortexa9hf-neon-oe-linux-gnueabi
```

Running `env` should yield a bunch of variables and a path that looks through the toolchain packages first. 

The next step will need to be run in the same terminal session to preserve env variables.

### 3. Build

```
$ git clone https://www.github.com/dixionary/draft-reMarkable
$ cd draft-reMarkable
$ qmake && make
$ file draft        # should say it's a 32-bit ARM executable
```

Sidenote: An example using a non-QT app that leverages the $CONFIGURE_FLAGS variable set up in the previous step:
```
wget https://mosh.org/mosh-1.3.2.tar.gz
tar -zxvf mosh-1.3.2.tar.gz
cd mosh-1.3.2
./configure $CONFIGURE_FLAGS
make
```
Again you can run `file src/frontend/mosh-client` to ensure it's an ARM binary that was produced.

### 4. Deploy

You can view debug logs for draft and any app that draft tries to launch by running `journalctl -fu draft`.

#### File reference
If you use the scripts above you shouldn't need to worry about these.
* `draft` binary goes in /usr/bin
* `mkdir -p /usr/share/draft/qml; mkdir -p /usr/share/draft js` all of the files in the `qml/` and `js/` directories should go into these folders
* Copy `extra-files/draft/` into `/etc/` so `/etc/draft/01-xochitl` etc exist. These are the files that define which apps to run and how, in addition to icons (see above for full details).
* Copy `extra-files/draft.service` to `/lib/systemd/system/draft.service` to install the systemd file. This will install
  draft as a system service. Then you'll need to `systemctl disable xochitl && systemctl enable draft` to replace
`xochitl` with `draft` as the startup app. Reboot, or to see it take effect right away, do `systemctl stop xochitl && systemctl start draft`.

* * * 
## Configure draft

Draft is configured through the files in the `/etc/draft` directory. They consist of a few simple lines. All of them are needed otherwise the option will not show up in the launcher.

`title`: Big word, left hand side of the screen.

`desc`: Smaller words, left hand side of the screen.

`call`: The shell command to run when the option is pressed.

`term`: The shell command to run while the option is running, to close it. (or it can do whatever you want really!) This won't do anything without `button-capture` installed.

`imgFile`: An icon to use. It will look for a PNG image with that name in the `/etc/draft/icons` directory.

*NOTE: Be sure not to leave any spaces around the "=" sign in the config lines, else the files may not parse correctly and your options may not show up!*
