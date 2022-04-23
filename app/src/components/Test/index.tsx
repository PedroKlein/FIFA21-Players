import React, { useState } from "react";
import "./styles.scss";

const Test: React.FC = () => {
  const [test, setTest] = useState("NAO");
  const [search, setSearch] = useState<string>();
  const calledFromCPP = () => {
    //@ts-ignore
    setTest(window["GetData"]()["data"]);
  };

  function onSubmit(e: React.FormEvent) {
    e.preventDefault();
    //@ts-ignore
    console.log(search);
    //@ts-ignore
    window["OnRequestSearch"](search);
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
          onChange={(e) => {
            setSearch(e.target.value);
          }}
        />
        <button type="submit">search</button>
      </form>
    </div>
  );
};

export default Test;
