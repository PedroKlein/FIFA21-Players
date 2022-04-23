import React, { useState } from "react";
import "./styles.scss";

const Test: React.FC = () => {
  const [test, setTest] = useState("NAO");
  const calledFromCPP = () => {
    //@ts-ignore
    setTest(window["GetData"]()["data"]);
  };

  function onSubmit(e: React.FormEvent<HTMLFormElement>) {
    e.preventDefault();
    //@ts-ignore
    window["OnRequestSearch"]("TEST SEARCH");
  }

  return (
    <div className="container">
      <button className="button-test" onClick={() => calledFromCPP()}>
        {test}
      </button>

      <form action="submit" onSubmit={onSubmit}>
        <input
          type="search"
          name="search"
          id="search"
          placeholder="search..."
        />
        <button type="submit">search</button>
      </form>
    </div>
  );
};

export default Test;
