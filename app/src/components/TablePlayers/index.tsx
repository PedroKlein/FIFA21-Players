import React from "react";
import { Player } from "../../@types/player.types";
import BaseTable from "../BaseTable";

interface IProps {
  players: Player[];
}
const TablePlayers: React.FC<IProps> = ({ players }) => {
  return (
    <BaseTable>
      <thead>
        <tr>
          <th>FifaID</th>
          <th>Name</th>
          <th>Positions</th>
          <th>Rating</th>
          <th>Count</th>
        </tr>
      </thead>
      <tbody>
        {players.map((p) => (
          <tr key={p.fifaID}>
            <td>{p.fifaID}</td>
            <td>{p.name}</td>
            <td>{p.positions}</td>
            <td>{p.rating.toFixed(6)}</td>
            <td>{p.count}</td>
          </tr>
        ))}
      </tbody>
    </BaseTable>
  );
};

export default TablePlayers;
