import React from "react";

import { Table } from "./styles";

const BaseTable: React.FC = ({ children }) => {
  return <Table>{children}</Table>;
};

export default BaseTable;
