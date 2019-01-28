let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => {
    let answers = ["Microsoft", "Atari", "Apple", "Commodore"];

    <div className="container">
      <h1 className="header"> {ReasonReact.string("COMPUTERS TRIVIA")} </h1>
      <div className="content">
        <h2 className="question">
          {ReasonReact.string(
             "Which company was established on April 1st, 1976 by Steve Jobs, Steve Wozniak and Ronald Wayne?",
           )}
        </h2>
        <div className="answersContainer">
          {answers
           |> List.map(answer =>
                <button className="answerButton">
                  {ReasonReact.string(answer)}
                </button>
              )
           |> Array.of_list
           |> ReasonReact.array}
        </div>
      </div>
    </div>;
  },
};