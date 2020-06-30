## Manual build setup without QT Creator

Steps to build and install without using scripts

- [Manual build setup without QT Creator](#manual-build-setup-without-qt-creator)
  * [1. Download and install source and toolchain](#1-download-and-install-source-and-toolchain)
  * [2. Activate environment](#2-activate-environment)
  * [3. Build](#3-build)
  * [4. Deploy](#4-deploy)
    + [File reference](#file-reference)
- [Configure draft](#configure-draft)

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
$ git clone https://www.github.com/dixonary/draft-reMarkable
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

### 4. Deploy (File reference)

Because of limited space on the root partition, it's better to install draft to /home/root.

```
/home/root/draft
├── etc
│   ├── 01-xochitl
│   ├── 02-fingerterm
│   ├── 99-shutdown
│   └── icons
│       ├── fingerterm.png
│       ├── power.png
│       └── xochitl.png
├── lib
│   └── systemd
│       └── system
│           └── draft.service
└── usr
    ├── bin
    │   └── draft
    └── share
        └── draft
            ├── js
            │   └── Main.js
            └── qml
                ├── Main.qml
                └── MenuItem.qml
```

To achieve this: 
* `draft` binary goes in usr/bin
* `mkdir -p usr/share/draft/qml; mkdir -p usr/share/draft js` all of the files in the `qml/` and `js/` directories should go into these folders
* Copy `extra-files/draft/` into `etc/` so `/etc/draft/01-xochitl` etc exist. These are the files that define which apps to run and how, in addition to icons (see above for full details).
* Copy `extra-files/draft.service` to `/lib/systemd/system/draft.service` to install the systemd file. 

(Note that paths are relative to /home/root/draft or your install directory of choice.

Finally, you'll want to link all of these files to the desired locations on the root partition:

```
cd /home/root/draft
find {etc,usr,lib} -type d -exec mkdir -p /{} \;
find {etc,usr,lib} -type f -exec ln -s /home/root/draft/{} /{} \;
```

This will install draft as a system service. Then you'll need to `systemctl enable draft && systemctl disable xochitl to replace
`xochitl` with `draft` as the startup app. Reboot, or to see it take effect right away, do `systemctl stop xochitl && systemctl start draft`.

