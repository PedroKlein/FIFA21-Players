import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";
import WrapView from "../../components/WrapView";
import styled from "styled-components";
import { isInteger } from "../../utils/isInteger";
import { CppBindings } from "../../@types/bindings.types";

const Form = styled.form`
  display: flex;
  align-items: center;
  margin-bottom: 10px;

  #topN {
    width: 40px;
    appearance: text;
    text-align: center;
    box-sizing: content-box;
    font-family: inherit;
    height: 15px;
    border: none;
    outline: none;
    margin-left: 10px;
    margin-right: 16px;
    background: var(--light-white);
    border: solid 1px var(--light);
    padding: 5px;
    border-radius: 10em;
    transition: all 0.5s;
  }
`;

const PositionSearch: React.FC = () => {
  const [position, setPosition] = useState("");
  const [topN, setTopN] = useState("20");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    if (position.length < 2 || topN.length == 0) return;

    setPlayers(CppBindings.onRequestPositionSearch(topN, position));
  }, [position, topN]);

  function handleChangeTopN(event: React.FormEvent<HTMLInputElement>): void {
    if (
      isInteger(event.currentTarget.value) &&
      +event.currentTarget.value <= 100
    )
      setTopN(event.currentTarget.value);
  }

  const debouncedSearch = useCallback(
    debounce((nextValue: string) => setPosition(nextValue), 20),
    []
  );

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    debouncedSearch(event.currentTarget.value);
  }

  return (
    <WrapView title="Position Search">
      <Form>
        <input
          id="topN"
          type="number"
          min={0}
          step={1}
          value={topN}
          onChange={handleChangeTopN}
          autoComplete="off"
        />
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="search bar"
        />
        <SearchBar
          type="search"
          placeholder="search by position..."
          onChange={handleChange}
          minLength={2}
          autoComplete="off"
          id="headerSearch"
          name="headerSearch"
          aria-labelledby="lbl-search-header"
        />
      </Form>
      <TablePlayers players={players} />
    </WrapView>
  );
};

export default PositionSearch;
