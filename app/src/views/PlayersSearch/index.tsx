import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import { Container } from "./styles";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";

const PLAYERS_MOCK: Player[] = [
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
  {
    fifaID: 123,
    name: "Pedro Klein",
    positions: "GM, AC, BT",
    rating: 4.77,
    count: 2000,
  }
];

const PlayersSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    if (search.length < 3) return;

    //@ts-ignore
    setPlayers(window["OnRequestPlayerSearch"](search));
    console.log(players);
  }, [search]);

  const debouncedSearch = useCallback(
    debounce((nextValue: string) => setSearch(nextValue), 500),
    []
  );

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    debouncedSearch(event.currentTarget.value);
  }

  function handleSubmit(event: React.FormEvent) {
    event.preventDefault();
  }

  return (
    <Container>
      <h2>Players Search</h2>
      <form onSubmit={handleSubmit}>
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="Barra de pesquisa"
        />
        <SearchBar
          placeholder="procurar..."
          onChange={handleChange}
          minLength={3}
          autoComplete="off"
          id="headerSearch"
          name="headerSearch"
          aria-labelledby="lbl-search-header"
        />
      </form>
      <TablePlayers players={PLAYERS_MOCK} />
    </Container>
  );
};

export default PlayersSearch;
