import styled from "styled-components";

export const Table = styled.table`
  width: 100%;
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
      height: 60px;
      background: #36304a;
    }
    th {
      font-size: 1.6rem;
      line-height: 1.2;
      font-weight: unset;
    }
  }

  tbody {
    display: block;
    overflow-y: scroll;
    height: 300px;
    tr {
      height: 60px;
      font-size: 1.6rem;
      color: #808080;
      line-height: 1.2;
      font-weight: unset;
      text-align: center;

      &:nth-child(even) {
        background-color: #f5f5f5;
      }
    }
  }
`;
