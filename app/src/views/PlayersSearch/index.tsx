import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";
import WrapView from "../../components/WrapView";
import { CppBindings } from "../../@types/bindings.types";

const PlayersSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    if (search.length < 3) return;
    setPlayers(CppBindings.onRequestPlayersSearch(search));
  }, [search]);

  const debouncedSearch = useCallback(
    debounce((nextValue: string) => setSearch(nextValue), 20),
    []
  );

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    debouncedSearch(event.currentTarget.value);
  }

  return (
    <WrapView title="Players Search">
      <form style={{ marginBottom: "10px" }}>
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
