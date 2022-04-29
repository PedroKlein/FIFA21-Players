import React from "react";
import { Player } from "../../@types/player.types";
import BaseTable from "../BaseTable";
import { Container } from "./styles";

interface IProps {
  players: Player[];
}
const TablePlayers: React.FC<IProps> = ({ players }) => {
  return (
    <Container>
      <BaseTable>
        <thead>
          <tr>
            <th id="fifaId">FifaID</th>
            <th id="name">Name</th>
            <th id="positions">Positions</th>
            <th id="rating">Rating</th>
            <th id="count">Count</th>
            <th id="void"></th>
          </tr>
        </thead>
        <tbody>
          {players.map((p) => (
            <tr key={p.fifaID}>
              <td id="fifaId">{p.fifaID}</td>
              <td id="name">{p.name}</td>
              <td id="positions">{p.positions}</td>
              <td id="rating">{p.rating.toFixed(6)}</td>
              <td id="count">{p.count}</td>
            </tr>
          ))}
        </tbody>
      </BaseTable>
    </Container>
  );
};

export default TablePlayers;
