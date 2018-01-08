# GitBook-Plugin-Vistors-GitHub

The GitHub Vistors Plugin for Gitbook. This plugin creates requests to corresonding GitHub source
page when from HTML documentation.

### Installation

```sh
$ npm install gitbook-plugin-vistors-github --save
```

### Usage

Add the following config in your `book.json`

```json
{
  "plugins": [
    "vistors-github"
  ],
  "pluginsConfig": {
    "vistors-github": {
      "repo": "...",
      "branch": "<optional>"
    }
  }
}
```

Under the `pluginsConfig.vistors-github`, the following properties:

- `repo`: What repository on GitHub do you want to redirect, like "Rokid/docs".
- `branch`: What branch name on specified `repo` do you want to redirect, default is "master".

### License

MIT