# npnoqol

## Commands

### `/setapikey <type> <apikey>`

Validates and saves an API key to `config.json`.

- `type` — `hypixel` or `zoo`

```
/setapikey hypixel xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
/setapikey zoo your_zoo_key
```

---

### `/denick <nick>`

Looks up the real username behind a nick.

```
/denick SomeNick
→ SomeNick is the nick of ActualPlayer
```

---

### `/find_nick <name>`

Looks up the nick a player is currently using.

```
/find_nick ActualPlayer
→ ActualPlayer is nicked as SomeNick
```
