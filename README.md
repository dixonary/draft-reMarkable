# draft-reMarkable
A launcher for the reMarkable tablet, which wraps around the standard interface.

* * *

## Setting up draft

### 1. Deploy draft
This should simply be a case of opening up qtcreator, loading up the project with the normal reMarkable target, and hitting "run".

As well as deploying the program, this will also populate `/etc/draft` with some sample commands and add a `/lib/systemd/system/draft.service` systemd file.


### 1.i (optional) Deploy button-capture

[This small program](https://github.com/dixonary/button-capture-reMarkable) allows you to close the current application and return to the draft launcher. There is no native way to close `xochitl` so this is a very useful thing to have if you want to switch between applications. 


### 1.ii (optional) Deploy fingerterm

[This terminal](https://github.com/dixonary/fingerterm-reMarkable) runs on the reMarkable and lets you change some config things without needing to SSH in! It's one of the default config options but you can remove that if you are't wanting to use it.

### 2. Enable draft at startup
You need to replace the normal xochitl startup with draft. This is done with the following two lines via SSH:

```bash
systemctl disable xochitl
systemctl enable draft
```

### 3. Restart your reMarkable

On restart you should find that `xochitl`, `fingerterm` and `shutdown` are your available choices and the draft launcher is running.

### 4. Configure draft

Draft is configured through the files in the `/etc/draft` directory. They consist of a few simple lines. All of them are needed otherwise the option will not show up in the launcher.

`title`: Big word, left hand side of the screen.
`desc`: Smaller words, left hand side of the screen.
`call`: The shell command to run when the option is pressed.
`term`: The shell command to run while the option is running, to close it. (or it can do whatever you want really!) This won't do anything without `button-capture` installed.
`imgFile`: An icon to use. It will look for a PNG image with that name in the `/etc/draft/icons` directory.

*NOTE: Be sure not to leave any spaces around the "=" sign in the config lines, else the files may not parse correctly and your options may not show up!*
