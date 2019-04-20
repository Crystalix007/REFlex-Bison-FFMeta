# What is this?
It's a parser for ffmpeg's ffmetadata format, which compresses multiline tags to HTML-formatted single lines for further manipulation.

# How do I build it?
You need:
* [TCLAP](http://tclap.sourceforge.net/)
* [RE-Flex](https://github.com/Genivia/RE-flex)
	* See [this repo](https://github.com/Crystalix007/PersonalAUR/tree/master/RE-flex) for a *PKGBUILD* for Arch Linux and derivatives.
* Bison
* GCC
* [Tup](https://github.com/gittup/tup)

Clone this repository.

Then simply run `tup init`, then `tup`, and the executable `FFMeta` should be produced.

# How do I use it?
You need `ffmpeg`, obviously.

Extract the FFMetadata from some media file with:

`ffmpeg -i FILENAME -f ffmetadata tags.txt`

Alternatively, use this ffmetadata file and save it as `tags.txt`:

```
;FFMETADATA1
GENRE=Pop
DATE=1964
track=01
ALBUM=All Summer Long
TITLE=I Get Around
ARTIST=The Beach Boys
album_artist=The Beach Boys
LYRICS=Round round get around\
I get around\
Yeah\
Get around round round I get around\
I get around\
Get around round round I get around\
From town to town\
Get around round round I get around\
I'm a real cool head\
Get around round round I get around\
I'm makin' real good bread\
\
I'm gettin' bugged driving up and down this same old strip\
I gotta finda new place where the kids are hip\
\
My buddies and me are getting real well known\
Yeah, the bad guys know us and they leave us alone\
\
I get around\
Get around round round I get around\
From town to town\
Get around round round I get around\
I'm a real cool head\
Get around round round I get around\
I'm makin' real good bread\
Get around round round I get around\
I get around\
Round\
Get around round round ooh\
Wah wa ooh\
Wah wa ooh\
Wah wa ooh\
\
We always take my car 'cause it's never been beat\
And we've never missed yet with the girls we meet\
\
None of the guys go steady cause it wouldn't be right\
To leave their best girl home on a Saturday night\
\
I get around\
Get around round round I get around\
From town to town\
Get around round round I get around\
I'm a real cool head\
Get around round round I get around\
I'm makin' real good bread\
Get around round round I get around\
I get around\
Round\
Ah ah ah ah ah ah ah ah\
\
Round round get around\
I get around\
Yeah\
Get around round round I get around\
Get around round round I get around\
Wah wa ooh\
Get around round round I get around\
Ooh ooh ooh\
Get around round round I get around\
Ooh ooh ooh\
Get around round round I get around\
Ooh ooh ooh\
Get around round round I get around\
Ooh ooh ooh
REPLAYGAIN_TRACK_PEAK=0.891251
REPLAYGAIN_TRACK_GAIN=-4.71 dB
```

Then, use the built binary to extract tags:

```bash
cat tags.txt | ./FFMeta --tag TITLE
```

Note that extracting tags currently has case sensitivity, so `--tag TITLE` is not the same as `--tag title`.
Multiple tags can be specified simultaneously.

If a tag contains newlines, these will be replaced with `<br />` tags, which should look correct when viewed as HTML.
To modify how newlines are represented, see `line 61` of `src/parser.yy`.
