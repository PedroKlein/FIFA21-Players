import React, { useEffect, useState } from "react";
import { Player } from "../../@types/player.types";
import TablePlayers from "../../components/TablePlayers";
import TagSearch from "../../components/TagSearch";
import WrapView from "../../components/WrapView";

const TagsSearch: React.FC = () => {
  const [tags, setTags] = useState<string[]>([]);
  const [players, setPlayers] = useState<Player[]>([]);

  useEffect(() => {
    //@ts-ignore
    setPlayers(window["OnRequestTagsSearch"](tags));
  }, [tags]);

  return (
    <WrapView title="Tags Search">
      <form style={{ marginBottom: "10px", width: "100%" }}>
        <label
          id="lbl-search-header"
          htmlFor="headerSearch"
          aria-label="search bar"
        />
        <TagSearch
          tags={tags}
          setTags={setTags}
          placeholder="add tag..."
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
