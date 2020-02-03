# draft-reMarkable
A launcher for the reMarkable tablet, which wraps around the standard interface.

[Draft v0.2 video](https://www.youtube.com/watch?v=VEngMK54SV4)

* * *

## Set-up

**This information is quite vague. Reddit user /u/prpletentacle wrote up their process for setting up Draft+rM, with the Plato app, here: https://www.reddit.com/r/RemarkableTablet/comments/bkbps9/how_to_install_plato_reader_and_add_it_to_draft/?st=jvp0mqus&sh=0651e353**

(nb. You fiddle with the internal system of your reMarkable at your own risk! Here be dragons.)

### 1. Setup QT Creator
To build draft you'll need to first set up QT Creator, which is covered on the [reMarkable wiki](https://remarkablewiki.com/devel/qt_creator).

### 2. Deploy draft
This should simply be a case of opening up qtcreator, loading up the project with the normal reMarkable target, and hitting "run".

As well as deploying the program, this will also populate `/etc/draft` with some sample commands and add a `/lib/systemd/system/draft.service` systemd file.


### 2.i (optional) Deploy button-capture

[This small program](https://github.com/dixonary/button-capture-reMarkable) allows you to close the current application and return to the draft launcher. There is no native way to close `xochitl` so this is a very useful thing to have if you want to switch between applications. 


### 2.ii (optional) Deploy fingerterm

[This terminal](https://github.com/dixonary/fingerterm-reMarkable) runs on the reMarkable and lets you change some config things without needing to SSH in! It's one of the default config options but you can remove that if you are't wanting to use it.

### 3. Enable at startup
You need to replace the normal xochitl startup with draft. This is done with the following two lines via SSH:

```bash
systemctl disable xochitl
systemctl enable draft
```

### 4. Restart your reMarkable

On restart you should find that `xochitl`, `fingerterm` and `shutdown` are your available choices and the draft launcher is running.

### 5. Configure draft

Draft is configured through the files in the `/etc/draft` directory. They consist of a few simple lines. All of them are needed otherwise the option will not show up in the launcher.

`title`: Big word, left hand side of the screen.

`desc`: Smaller words, left hand side of the screen.

`call`: The shell command to run when the option is pressed.

`term`: The shell command to run while the option is running, to close it. (or it can do whatever you want really!) This won't do anything without `button-capture` installed.

`imgFile`: An icon to use. It will look for a PNG image with that name in the `/etc/draft/icons` directory.

*NOTE: Be sure not to leave any spaces around the "=" sign in the config lines, else the files may not parse correctly and your options may not show up!*
