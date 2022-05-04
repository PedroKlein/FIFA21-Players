import styled from "styled-components";
import { device } from "../../@types/devices.types";

export const Container = styled.div`
  position: relative;
  label {
    position: absolute;
    left: 15px;
    top: 3px;
    cursor: pointer;
    /* @media ${device.tablet} {
      left: 17px;
      top: 6px;
    } */
  }
  input {
    appearance: text;
    box-sizing: content-box;
    font-family: inherit;
    width: 220px;
    height: 15px;
    border: none;
    outline: none;
    margin-left: 10px;
    margin-right: 16px;
    background: var(--light-white);
    border: solid 1px var(--light);
    padding: 5px 10px 5px 32px;
    border-radius: 10em;
    transition: all 0.5s;
    /* @media ${device.tablet} {
      padding: 9px 10px 9px 32px;
      width: 15px;
      padding-left: 10px;
      color: transparent;
      cursor: pointer;
      &:hover {
        background-color: var(--light);
      }
      &:focus {
        width: 130px;
        padding-left: 32px;
        color: #000;
        background-color: #fff;
        cursor: auto;
      }
      &::placeholder {
        color: transparent;
      }
    } */
  }
`;
