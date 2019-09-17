# fork of draft-reMarkable
A launcher for the reMarkable tablet, which wraps around the standard interface.

[Draft v0.2 video](https://www.youtube.com/watch?v=VEngMK54SV4)

* * *

## Set-up
(nb. You fiddle with the internal system of your reMarkable at your own risk! Here be dragons.)

### 1. Deploy draft
```bash
source thetoolchain
qmake
make
scp bin/draft rm:
```
or
```
./dep.sh
```

### 2.a Enable at startup
You need to replace the normal xochitl startup with draft. This is done with the following two lines via SSH:

```bash
systemctl disable xochitl
systemctl enable draft
```

### 2.b Use touchgestures
TODO



### 4. Configure draft

Draft is configured through the files in the `~/.config/draft` directory. They consist of a few simple lines. All of them are needed otherwise the option will not show up in the launcher.

`title`: Big word, left hand side of the screen.

`desc`: Smaller words, left hand side of the screen.

`call`: The shell command to run when the option is pressed.

not implemented yet:
`term`: The shell command to run while the option is running, to close it. (or it can do whatever you want really!) This won't do anything without `button-capture` installed.

`imgFile`: An icon to use. It will look for a PNG image with that name in the `/etc/draft/icons` directory.

*NOTE: Be sure not to leave any spaces around the "=" sign in the config lines, else the files may not parse correctly and your options may not show up!*
