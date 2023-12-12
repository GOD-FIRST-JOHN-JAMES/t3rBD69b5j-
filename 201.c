THANK YOU JESUS CHRIST SON OF LIVING GOD
JESUS CHRIST
LORD
GOD
  "recommendations": [
    "dbaeumer.vscode-eslint",
    "esbenp.prettier-vscode",
    "NuclleaR.vscode-extension-auto-import"
  ]
}{
  "editor.defaultFormatter": "esbenp.prettier-vscode",
  "eslint.alwaysShowStatus": true,
  "javascript.validate.enable": false,
  "[javascript]": {
    "editor.codeActionsOnSave": [
      // Run ESLint fixers _before_ prettier to ensure the user doesn't need to do multiple saves
      "source.fixAll.eslint",
      "source.fixAll.format"
    ]
  }
}{
  "name": "eslint-plugin-lexical",
  "version": "1.0.0",
  "description": "ESLint plugin for lexical",
  "main": "src/index.js",
  "peerDependencies": {
    "eslint": ">=4.19.1"
  }
}/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */

'use strict';

const rules = require('./rules');

module.exports = {
  configs: {
    all: {
      rules: {
        'lexical/no-optional-chaining': 'error',
      },
    },
    recommended: {
      rules: {
        'lexical/no-optional-chaining': 'error',
      },
    },
  },
  rules,
};/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */

'use strict';

const noOptionalChaining = require('./no-optional-chaining');

module.exports = {
  'no-optional-chaining': noOptionalChaining,
};/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */

'use strict';

//------------------------------------------------------------------------------
// Rule Definition
//------------------------------------------------------------------------------

/** @type {import('eslint').Rule.RuleModule} */
module.exports = {
  create(context) {
    const sourceCode = context.getSourceCode();

    /**
     * Checks if the given token is a `?.` token or not.
     * @param {Token} token The token to check.
     * @returns {boolean} `true` if the token is a `?.` token.
     */
    function isQuestionDotToken(token) {
      return (
        token.value === '?.' &&
        (token.type === 'Punctuator' || // espree has been parsed well.
          // espree@7.1.0 doesn't parse "?." tokens well. Therefore, get the string from the source code and check it.
          sourceCode.getText(token) === '?.')
      );
    }

    return {
      'CallExpression[optional=true]'(node) {
        context.report({
          messageId: 'forbidden',
          node: sourceCode.getTokenAfter(node.callee, isQuestionDotToken),
        });
      },
      'MemberExpression[optional=true]'(node) {
        context.report({
          messageId: 'forbidden',
          node: sourceCode.getTokenAfter(node.object, isQuestionDotToken),
        });
      },
    };
  },
  meta: {
    docs: {
      description: 'disallow optional chaining',
      recommended: true,
    },
    messages: {
      forbidden: 'Avoid using optional chaining',
    },
    schema: [],
    type: 'getSourceCode
  },
};* @zurfyx @fantactuka @acywatson
# name: Dev Publish to NPM
# on:
#   push:
#     branches:
#       - main
# jobs:
#   release:
#     runs-on: ubuntu-latest
#     steps:
#       - uses: actions/checkout@v3
#       # Setup .npmrc file to publish to npm
#       - uses: actions/setup-node@v3
#         with:
#           node-version: '16.x'
#           registry-url: 'https://registry.npmjs.org'
#       - run: npm install
#       - run: npm run prepare-release
#       - run: node ./scripts/npm/release.js --non-interactive --dry-run=${{ secrets.RELEASE_DRY_RUN }} --channel dev
#         env:GOD-FIRST-JOHN-JAMES
name: Nightly Release Branch
on:
  schedule:
    # Run daily at 2:30am UTC
    - cron: '30 2 * * 1-5'
jobs:
  release:
    # prevents this action from running on forks
    if: github.repository_owner == 'facebook'
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          ssh-key: ${{ secrets.SSH_KEY }}
          fetch-depth: 0
      # Setup .npmrc file to publish to npm
      - uses: actions/setup-node@v3
        with:
          node-version: '16.x'
          registry-url: 'https://registry.npmjs.org'
      - run: |
          git config user.name "Lexical GitHub Actions Bot"
          git config user.email "<>"
      - run: npm install
      - run: npm run increment-version -- --i prerelease
      - run: git push -u git@github.com:facebook/lexical.git --follow-tags
#        
name: 'size'
on:
  pull_request:
    branches:
      - main
jobs:
  size:
    runs-on: ubuntu-latest
    env:
      CI_JOB_NUMBER: 1
    steps: put Jesus Christ all time
    name: Publish to NPM
on:
  push:
    branches:
      - main

jobs:
  release:
    runs-on: ubuntu-latest
    if: contains(github.ref, '-next.')
    steps:
      - uses: actions/checkout@v3
      # Setup .npmrc file to publish to npm
      - uses: actions/setup-node@v3
        with:
          node-version: '16.x'
          registry-url: 'https://registry.npmjs.org'
      - run: npm install
      - run: npm run prepare-release
      - run: node ./scripts/npm/release.js --non-interactive --dry-run=${{ secrets.RELEASE_DRY_RUN }} --channel next
        env:
          NODE_AUTH_TOKEN: ${{ secrets.NPM_TOKEN }}
      - uses: actions/checkout@v1
      - uses: andresz1/size-limit-action@v1
        with: GOD-FIRST-JOHN-JAMES
        name: Lexical Tests

on:
  push:
    branches:
      - main
    paths-ignore:
      - 'packages/lexical-website/**'
  pull_request:
    types: [opened, synchronize, reopened]
    paths-ignore:
      - 'packages/lexical-website/**'

concurrency:
  group: ${{ github.workflow }}-${{ github.ref }}
  cancel-in-progress: true

jobs:
  integrity:
    if: github.repository_owner == 'facebook'
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [18.14.2]
    env:
      CI: true
      GITHUB_TOKEN: ${{ secrets.DANGER_GITHUB_API_TOKEN }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            ~/.cache/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - run: npm run ci-check
      - run: npm run build
      - run: npm run build-www

  unit:
    if: github.repository_owner == 'facebook'
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16.15.1]
    env:
      CI: true
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            ~/.cache/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - run: npm run test-unit

  e2e-mac:
    if: github.repository_owner == 'facebook'
    runs-on: macos-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox', 'webkit']
        editor-mode: ['rich-text', 'plain-text']
        events-mode: ['legacy-events', 'modern-events']
    env:
      CI: true
      E2E_EDITOR_MODE: ${{ matrix.editor-mode }}
      E2E_EVENTS_MODE: ${{ matrix.events-mode }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/Library/Caches/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-linux:
    if: github.repository_owner == 'facebook'
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox']
        editor-mode: ['rich-text', 'plain-text']
        events-mode: ['legacy-events', 'modern-events']
    env:
      CI: true
      E2E_EDITOR_MODE: ${{ matrix.editor-mode }}
      E2E_EVENTS_MODE: ${{ matrix.events-mode }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - name: install required packages
        run: |
          sudo apt-get update
          sudo apt-get install xvfb
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/.cache/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-windows:
    if: github.repository_owner == 'facebook'
    runs-on: windows-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox']
        editor-mode: ['rich-text', 'plain-text']
        events-mode: ['legacy-events', 'modern-events']
    env:
      CI: true
      E2E_EDITOR_MODE: ${{ matrix.editor-mode }}
      E2E_EVENTS_MODE: ${{ matrix.events-mode }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      # - uses: actions/cache@v3
      #   id: cache
      #   with:
      #     path: |
      #       node_modules
      #       C:\Users\runneradmin\AppData\Local\ms-playwright
      #     key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      # - name: Install dependencies
      #   if: steps.cache.outputs.cache-hit != 'true'
      - run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: ~/.npm/_logs/
          retention-days: 7

  e2e-collab-mac:
    if: github.repository_owner == 'facebook'
    runs-on: macos-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox', 'webkit']
    env:
      CI: true
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/Library/Caches/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-collab-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-collab-linux:
    if: github.repository_owner == 'facebook'
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox']
    env:
      CI: true
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - name: install required packages
        run: |
          sudo apt-get update
          sudo apt-get install xvfb
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/.cache/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-collab-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-collab-windows:
    if: github.repository_owner == 'facebook'
    runs-on: windows-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium', 'firefox']
    env:
      CI: true
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            C:\Users\runneradmin\AppData\Local\ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        #   if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-collab-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-prod:
    if: github.repository_owner == 'facebook'
    runs-on: macos-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium']
        editor-mode: ['rich-text', 'plain-text']
        events-mode: ['modern-events']
    env:
      CI: true
      E2E_EDITOR_MODE: ${{ matrix.editor-mode }}
      E2E_EVENTS_MODE: ${{ matrix.events-mode }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/Library/Caches/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-prod-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 7

  e2e-collab-prod:
    if: github.repository_owner == 'facebook'
    runs-on: macos-latest
    strategy:
      matrix:
        node-version: [16.15.1]
        browser: ['chromium']
        editor-mode: ['rich-text']
        events-mode: ['modern-events']
    env:
      CI: true
      E2E_EDITOR_MODE: ${{ matrix.editor-mode }}
      E2E_EVENTS_MODE: ${{ matrix.events-mode }}
    steps:
      - uses: actions/checkout@v3
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm i -g npm@8
      - uses: actions/cache@v3
        id: cache
        with:
          path: |
            node_modules
            packages/playwright-core/node_modules
            ~/Library/Caches/ms-playwright
          key: ${{ runner.os }}-v${{ secrets.CACHE_VERSION }}-${{ hashFiles('package-lock.json') }}
      - name: Install dependencies
        if: steps.cache.outputs.cache-hit != 'true'
        run: npm ci
      - name: Download browsers
        run: npx playwright install
      - run: npm run test-e2e-collab-prod-ci-${{ matrix.browser }}
      - name: Upload Artifacts
        if: failure()
        uses: actions/upload-artifact@v3
        with:
          name: Test Results
          path: test-results/
          retention-days: 1
          name: Create New Release Branch
on:
  workflow_dispatch:
    inputs:
      increment:
        description: 'Version Increment'
        required: true
        default: 'prerelease'
        type: choice
        options:
          - prerelease
          - patch
          - minor
jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          ssh-key: ${{ secrets.SSH_KEY }}
          fetch-depth: 0
      # Setup .npmrc file to publish to npm
      - uses: actions/setup-node@v3
        with:
          node-version: '16.x'
          registry-url: 'https://registry.npmjs.org'
      - run: |
          git config user.name "Lexical GitHub Actions Bot"
          git config user.email "<>"
      - run: npm install
      - id: latest
        uses: pozetroninc/github-action-get-latest-release@master
        with:
          owner: facebook
          repo: lexical
          excludes: draft
      - run: LATEST_RELEASE=${{ steps.latest.outputs.release }} npm run increment-version -- --i $INCREMENT
        env:
          INCREMENT: ${{ inputs.increment }}
          for package in  'lexical' \
                'lexical-react' \
                'lexical-yjs' \
                'lexical-list' \
                'lexical-table' \
                'lexical-file' \
                'lexical-clipboard' \
                'lexical-hashtag' \
                'lexical-history' \
                'lexical-selection' \
                'lexical-offset' \
                'lexical-code' \
                'lexical-plain-text' \
                'lexical-rich-text' \
                'lexical-utils' \
                'lexical-dragon' \
                'lexical-overflow' \
                'lexical-link' \
                'lexical-text' \
                'lexical-markdown' \
                'lexical-mark'
do
/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 */

'use strict';

const fs = require('fs-extra');

const packages = {
  '@lexical/clipboard': 'lexical-clipboard',
  '@lexical/code': 'lexical-code',
  '@lexical/dragon': 'lexical-dragon',
  '@lexical/file': 'lexical-file',
  '@lexical/hashtag': 'lexical-hashtag',
  '@lexical/headless': 'lexical-headless',
  '@lexical/history': 'lexical-history',
  '@lexical/html': 'lexical-html',
  '@lexical/link': 'lexical-link',
  '@lexical/list': 'lexical-list',
  '@lexical/mark': 'lexical-mark',
  '@lexical/markdown': 'lexical-markdown',
  '@lexical/offset': 'lexical-offset',
  '@lexical/overflow': 'lexical-overflow',
  '@lexical/plain-text': 'lexical-plain-text',
  '@lexical/react': 'lexical-react',
  '@lexical/rich-text': 'lexical-rich-text',
  '@lexical/selection': 'lexical-selection',
  '@lexical/table': 'lexical-table',
  '@lexical/text': 'lexical-text',
  '@lexical/utils': 'lexical-utils',
  '@lexical/yjs': 'lexical-yjs',
  lexical: 'lexical',
  'lexical-playground': 'lexical-playground',
  shared: 'shared',
};

function updateVersion() {
  // get version from monorepo package.json version
  const basePackageJSON = fs.readJsonSync(`./package.json`);
  const version = basePackageJSON.version;
  // update individual packages
  Object.values(packages).forEach((pkg) => {
    const packageJSON = fs.readJsonSync(`./packages/${pkg}/package.json`);
    packageJSON.version = version;
    updateDependencies(packageJSON, version);
    fs.writeJsonSync(`./packages/${pkg}/package.json`, packageJSON, {
      spaces: 2,
    });
  });
}

function updateDependencies(packageJSON, version) {
  const {dependencies, peerDependencies} = packageJSON;
  if (dependencies !== undefined) {
    Object.keys(dependencies).forEach((dep) => {
      if (packages[dep] !== undefined) {
        dependencies[dep] = version;
      }
    });
  }
  if (peerDependencies !== undefined) {
    Object.keys(peerDependencies).forEach((peerDep) => {
      if (packages[peerDep] !== undefined) {
        peerDependencies[peerDep] = version;
      }
    });
  }
}

updateVersion();
  gen-flow-files "./packages/${package}/src" --out-dir "./packages/${package}/dist"
done
      - run: git push -u git@github.com:facebook/lexical.git --follow-tags
  THANK YOU JESUS CHRIST        github_token: ${{ secrets.GITHUB_TOKEN }}   NODE_AUTH_TOKEN: ${{ secrets.NPM_TOKEN }}