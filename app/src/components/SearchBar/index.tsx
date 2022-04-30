import { DetailedHTMLProps, forwardRef, InputHTMLAttributes } from "react";
import { BsSearch } from 'react-icons/bs'
import { Container } from "./styles";

const SearchBar: React.ForwardRefRenderFunction<
  HTMLInputElement,
  DetailedHTMLProps<InputHTMLAttributes<HTMLInputElement>, HTMLInputElement>
> = ({ ...rest }, ref) => {
  return (
    <Container>
      <label htmlFor={rest.id || "search"}>
        {/* <svg
          xmlns="http://www.w3.org/2000/svg"
          width="20"
          height="20"
          viewBox="0 0 20 20"
          fill="transparent"
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            strokeWidth={2}
            stroke="var(--secondary-dark)"
            d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"
          />
        </svg> */}
        <BsSearch color="var(--secondary-dark)" size={20} title="search" />
      </label>
      <input {...rest} ref={ref} />
    </Container>
  );
};

export default forwardRef(SearchBar);
