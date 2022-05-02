import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";
import WrapView from "../../components/WrapView";

const PlayersSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    if (search.length < 3) return;
    //@ts-ignore
    setPlayers(window["OnRequestPlayersSearch"](search));
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
      <TablePlayers players={players} />
    </WrapView>
  );
};

export default PlayersSearch;
