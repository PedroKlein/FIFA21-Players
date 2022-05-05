import { Player } from "./player.types";
import { UserRating } from "./userRating.types";

interface ICppBindings {
  onRequestPlayersSearch: (search: string) => Player[];
  onRequestUserSearch: (userID: string) => UserRating[];
  onRequestPositionSearch: (topN: string, position: string) => Player[];
  onRequestTagsSearch: (tags: string[]) => Player[];
}

function onRequestPlayersSearch(search: string): Player[] {
  //@ts-ignore
  return window["OnRequestPlayersSearch"](search);
}

function onRequestUserSearch(userID: string): UserRating[] {
  //@ts-ignore
  return window["OnRequestUserSearch"](userID);
}

function onRequestPositionSearch(topN: string, position: string): Player[] {
  //@ts-ignore
  return window["OnRequestPositionSearch"](topN, position);
}

function onRequestTagsSearch(tags: string[]): Player[] {
  //@ts-ignore
  return window["OnRequestTagsSearch"](tags);
}

export const CppBindings: ICppBindings = {
  onRequestPlayersSearch,
  onRequestUserSearch,
  onRequestPositionSearch,
  onRequestTagsSearch,
};
