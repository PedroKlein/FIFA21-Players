import React, { useEffect, useState } from "react";
import SearchBar from "../../components/SearchBar";
import WrapView from "../../components/WrapView";
import { UserRating } from "../../@types/userRating.types";
import TableUserRatings from "../../components/TableUserRatings";
import { isInteger } from "../../utils/isInteger";
import { CppBindings } from "../../@types/bindings.types";

const UserSearch: React.FC = () => {
  const [userID, setUserID] = useState("");
  const [userRatings, setUserRatings] = useState<UserRating[]>([]);

  useEffect(() => {
    if (isInteger(userID) && userID.length > 0)
      setUserRatings(CppBindings.onRequestUserSearch(userID));
  }, [userID]);

  function handleChange(event: React.FormEvent<HTMLInputElement>): void {
    if (isInteger(event.currentTarget.value))
      setUserID(event.currentTarget.value);
  }

  return (
    <WrapView title="User Search">
      <form style={{ marginBottom: "10px" }}>
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
          value={userID}
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
