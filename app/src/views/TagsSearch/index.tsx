import React, { useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import WrapView from "../../components/WrapView";

const PLAYERS_MOCK: Player[] = [
  {
    fifaID: 132123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein dawdawsd awdsasdwd ",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT,",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  },
];

const TagsSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    console.log(players);
    console.log(PLAYERS_MOCK);
  }, [search]);

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    setSearch(event.currentTarget.value);
  }

  function handleSubmit(event: React.FormEvent) {
    event.preventDefault();
    //@ts-ignore
    setPlayers(window["OnRequestPlayersSearch"](search));
  }

  return (
    <WrapView title="Tags Search">
      <form onSubmit={handleSubmit} style={{ marginBottom: "10px" }}>
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="search bar"
        />
        <SearchBar
          placeholder="search..."
          onChange={handleChange}
          autoComplete="off"
          id="headerSearch"
          name="headerSearch"
          aria-labelledby="lbl-search-header"
        />
      </form>
      <TablePlayers players={players} />
    </WrapView>
  );
};

export default TagsSearch;
