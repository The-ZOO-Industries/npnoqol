# npnoqol

## `/setapikey` Command

Validates and saves an API key for use with the client.

### Usage

```
/setapikey <type> <apikey>
```

| Argument | Description |
|----------|-------------|
| `type`   | The API type — either `hypixel` or `zoo` |
| `apikey` | Your API key |

### Examples

```
/setapikey hypixel xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
/setapikey zoo your_zoo_api_key_here
```

### How It Works

The command validates the key against the respective API before saving it. If the key is accepted, it is stored in `config.json` and a green confirmation message is shown in chat. If the key is rejected, a red error message is shown and nothing is saved.

- **hypixel** — sends a request to the Hypixel API (`/v2/key`) to verify the key
- **zoo** — sends a request to the Zoo API (`/check_key`) to verify the key

### Notes

- The command is processed asynchronously; there may be a brief delay while the key is being validated.
- Saved keys persist across sessions via `config.json`.
