import React from "react";
import { Player } from "../../@types/player.types";
import { UserRating } from "../../@types/userRating.types";
import BaseTable from "../BaseTable";
import { Container } from "./styles";

interface IProps {
  userRatings: UserRating[];
}
const TableUserRatings: React.FC<IProps> = ({ userRatings }) => {
  return (
    <Container>
      <BaseTable>
        <thead>
          <tr>
            <th id="fifaId">FifaID</th>
            <th id="name">Name</th>
            <th id="globalRating">Global Rating</th>
            <th id="count">Count</th>
            <th id="rating">Rating</th>
            <th id="void"></th>
          </tr>
        </thead>
        <tbody>
          {userRatings.map((u) => (
            <tr key={u.fifaID}>
              <td id="fifaId">{u.fifaID}</td>
              <td id="name">{u.name}</td>
              <td id="globalRating">{u.globalRating.toFixed(6)}</td>
              <td id="count">{u.count}</td>
              <td id="rating">{u.rating.toFixed(6)}</td>
            </tr>
          ))}
        </tbody>
      </BaseTable>
    </Container>
  );
};

export default TableUserRatings;
