# Hello World

```shell
npm install -g bs-platform
git clone https://github.com/moroshko/reason-react-tutorial.git
cd reason-react-tutorial
git checkout 01-hello-world
npm install
```

To tell [`bsb`](https://bucklescript.github.io/docs/en/interop-overview#build-system) to compile all `.re` files to `.bs.js` files in watch mode:
```shell
npm start
```

To bundle all the generated `.bs.js` files into a single `Index.js` (which is included in our `index.html`), run the Webpack DevServer:
```shell
npm run server
```

Open http://localhost:8000/ and you should see "Hello World".

If you modify now any of the `.re` files and save it, `bsb` will recompile it, Webpack will create a new bundle, and your page will be automatically updated. Hot reloading for the win :tada:

## Let's see how it works

Our entry file is `Index.re`, and it's very simple:

```reason
ReactDOMRe.renderToElementWithId(<App />, "app");
```

<details>
<summary>This looks familiar to me!</summary>
<br>

Yep, it's very similar to how React renders the `App` component to a DOM element with `id="app"`: 

```javascript
ReactDOM.render(<App />, document.getElementById('app'))
```
Note that `index.html` contains:
```html
<div id="app"></div>
```
</details>
<br>

Let's see what our `<App />` does

```reason
let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Hello World")} </div>,
};
```

<details>
<summary>I don't know what a stateless component is, and this syntax doesn't make a lot of sense to me :confused:</summary>
<br>

This tutorial assumes a basic knowledge of [React](https://reactjs.org/docs/hello-world.html) and [Reason syntax](https://reasonml.github.io/docs/en/let-binding). Please follow these links to learn the basics first.
</details>
<br>

<details>
<summary>What is this `make` function?</summary>
<br>

ReasonReact's JSX desugars `<App />` to `App.make(...)`. Therefore, every component **must** define a `make` function.
</details>
<br>

<details>
<summary>What is `{ ...component, render: ... }` doing?</summary>
<br>

You can think of it as extending `React.Component` in React and defining our own `render` function.
</details>
<br>

<details>
<summary>What is `_children`?</summary>
<br>

In React, components can have children, e.g.:
```javascript
<Header>
  <Logo />
  <Title>My Todos</Title>
</Header>
```
The `Header` component has two children here, `Logo` and `Title`.

In our case, `<App />` doesn't have children. As you can see, `_children` is not used in `make`. 

However, we **must** define the `children` parameter. We prepend `children` with `_` to tell the compiler that it's unused so it won't trigger warnings.
</details>
<br>

<details>
<summary>What is `_self`?</summary>
<br>

`self` gives us access to lots of useful things like state, lifecycle hooks, etc.
We don't use any of these yet, so we prepend it with `_`.
</details>
<br>

<details>
<summary>Why do we call `ReasonReact.string`. It's really verbose compared to React. I don't like it.</summary>
<br>

This is because of the **strict type system** Reason has.

In ReasonReact, children must be of type `ReasonReact.reactElement`, so we must use helpers like:
* `ReasonReact.string`
* `ReasonReact.array`
* `ReasonReact.null`

which all return a `ReasonReact.reactElement`.
</details>
<br>

