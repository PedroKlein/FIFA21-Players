import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";
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

const PlayersSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    if (search.length < 3) return;

    //@ts-ignore
    setPlayers(window["OnRequestPlayersSearch"](search));
    console.log(players);
    console.log(PLAYERS_MOCK);
  }, [search]);

  const debouncedSearch = useCallback(
    debounce((nextValue: string) => setSearch(nextValue), 20),
    []
  );

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    debouncedSearch(event.currentTarget.value);
  }

  function handleSubmit(event: React.FormEvent) {
    event.preventDefault();
  }

  return (
    <WrapView title="Players Search">
      <form onSubmit={handleSubmit} style={{ marginBottom: "10px" }}>
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="search bar"
        />
        <SearchBar
          type={"search"}
          placeholder="search..."
          onChange={handleChange}
          minLength={3}
          autoComplete="off"
          id="headerSearch"
          name="headerSearch"
          aria-labelledby="lbl-search-header"
        />
      </form>
      <TablePlayers players={PLAYERS_MOCK} />
    </WrapView>
  );
};

export default PlayersSearch;
