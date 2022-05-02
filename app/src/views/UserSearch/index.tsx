import React, { useCallback, useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import SearchBar from "../../components/SearchBar";
import TablePlayers from "../../components/TablePlayers";
import { debounce } from "../../utils/debounce";
import WrapView from "../../components/WrapView";
import { UserRating } from "../../@types/userRating.types";
import TableUserRatings from "../../components/TableUserRatings";

const USER_RATINGS_MOCK: UserRating[] = [
  {
    fifaID: 132123,
    name: "Pedro Klein",
    globalRating: 2.43533523523542,
    rating: 4.77,
    count: 2000,
  },
];

const UserSearch: React.FC = () => {
  const [search, setSearch] = useState("");
  const [userRatings, setUserRatings] = useState<UserRating[]>([]);

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    if (isValidInput(event.currentTarget.value))
      setSearch(event.currentTarget.value);
  }

  function handleSubmit(event: React.FormEvent) {
    event.preventDefault();
    if (isValidInput(search) && search.length > 0)
      //@ts-ignore
      setUserRatings(window["OnRequestUserSearch"](search));
  }

  function isValidInput(str: string): boolean {
    return str.match(/\s*|^[0-9]\d*$/)?.length == 1;
  }

  return (
    <WrapView title="User Search">
      <form onSubmit={handleSubmit} style={{ marginBottom: "10px" }}>
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="search bar"
        />
        <SearchBar
          type="number"
          placeholder="search by userID..."
          min={0}
          step={1}
          value={search}
          onChange={handleChange}
          autoComplete="off"
          id="headerSearch"
          name="headerSearch"
          aria-labelledby="lbl-search-header"
        />
      </form>
      <TableUserRatings userRatings={userRatings} />
    </WrapView>
  );
};

export default UserSearch;
