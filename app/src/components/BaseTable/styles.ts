import styled from "styled-components";

export const Table = styled.table`
  table-layout: fixed;
  max-width: 100%;
  min-width: 500px;
  background: var(--light-white);
  border-collapse: collapse;
  border-spacing: 1;
  overflow: hidden;
  border-radius: 10px;

  thead {
    display: inline-table;
    width: 100%;
    tr {
      text-align: left;
      height: 60px;
      background: #36304a;
    }
    th {
      padding: 10px;
      font-size: 1.6rem;
      font-weight: unset;
    }
  }

  tbody {
    display: block;
    overflow-y: scroll;
    height: 50vh;

    tr {
      height: 60px;
      font-size: 1.6rem;
      color: #808080;
      font-weight: unset;
      text-align: left;

      &:nth-child(even) {
        background-color: #f5f5f5;
      }

      td {
        padding: 10px;
      }
    }
  }
`;
