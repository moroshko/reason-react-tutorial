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
<summary>
(Click here to reveal details)

This looks familiar to me!</summary>

Yep, it's very similar to how ReactJS renders the `App` component to a DOM element with `id="app"`: 

```javascript
ReactDOM.render(<App />, document.getElementById('app'))
```
Note that `index.html` contains:
```html
<div id="app"></div>
```
</details>

Let's see what our `<App />` does:

```reason
let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Hello World")} </div>,
};
```

<details>
<summary>

I don't know what a stateless component is, and this syntax doesn't make a lot of sense to me :confused:</summary>

This tutorial assumes a basic knowledge of [React](https://reactjs.org/docs/hello-world.html) and [Reason syntax](https://reasonml.github.io/docs/en/let-binding). Please follow these links to learn the basics.
</details>

<details>
<summary>

What is this `make` function?</summary>

ReasonReact's JSX desugars `<App />` to `App.make(...)`. 
Therefore, every component **must** define a `make` function.
</details>

<details>
<summary>

What is `{ ...component, render: ... }` doing?</summary>

You can think of it as extending `React.Component` in ReactJS and defining our own `render` function.
</details>

<details>
<summary>

Can't I inline `let component` like this?
```reason
let make = _children => {
  ...(ReasonReact.statelessComponent("App")),
  render: ...
};
```
</summary>

Although it will compile, **it's not a good idea!**

Inlining this way means that you'll be creating a brand new component every time the `make` function is called.
</details>

<details>
<summary>

What is `_children`?</summary>

In our case, `<App />` is called without children. But, if we had, for example:
```javascript
<App>
  <Header />
  <Content />
</App>
```
then `_children` would be an array of length 2.

As you can see, `_children` is not used in `make`. However, we **must** define the `children` parameter. We prepend `children` with `_` to tell the compiler that it's unused so it doesn't trigger warnings.
</details>


<details>
<summary>

What is `_self`?</summary>

`self` gives us access to lots of useful things like state, lifecycle hooks, etc.
We don't use any of these yet, so we prepend it with `_`.
</details>

<details>
<summary>

Why do we call `ReasonReact.string`. It's really verbose compared to React. I don't like it.</summary>

This is because of the **strict type system** Reason has.

In ReasonReact, children must be of type `ReasonReact.reactElement`, so we must use helpers like:
* `ReasonReact.string`
* `ReasonReact.array`
* `ReasonReact.null`

which all return a `ReasonReact.reactElement`.
</details>

