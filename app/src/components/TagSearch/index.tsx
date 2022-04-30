import {
  DetailedHTMLProps,
  Dispatch,
  InputHTMLAttributes,
  SetStateAction,
  useRef,
  useState,
} from "react";
import {
  BsFillPlusCircleFill,
  BsFillXCircleFill,
  BsSearch,
} from "react-icons/bs";
import { Bar, Container, Tags } from "./styles";

interface IProps {
  tags: string[];
  setTags: Dispatch<SetStateAction<string[]>>;
}
type Props = IProps &
  DetailedHTMLProps<InputHTMLAttributes<HTMLInputElement>, HTMLInputElement>;
const TagSearch: React.FC<Props> = ({ tags, setTags, ...rest }) => {
  const [input, setInput] = useState("");
  const inputRef = useRef<HTMLInputElement>(null);

  function handleAdd() {
    if (input.length > 0) setTags((old) => [...old, input]);
    if (inputRef.current) inputRef.current.value = "";
  }

  function handleDelete(i: number) {
    let newTags = [...tags];
    newTags.splice(i, 1);
    setTags(newTags);
  }

  return (
    <Container>
      <Bar>
        <label htmlFor={rest.id || "search"}>
          <BsSearch color="var(--secondary-dark)" size={20} title="search" />
        </label>
        <input
          {...rest}
          ref={inputRef}
          onChange={(e) => setInput(e.currentTarget.value)}
        />
        <button type="button" onClick={() => handleAdd()}>
          <BsFillPlusCircleFill color="var(--success)" size={24} title="add" />
        </button>
      </Bar>

      <Tags>
        {tags.map((tag, i) => (
          <div key={i}>
            <span>{tag}</span>
            <button type="button" onClick={() => handleDelete(i)}>
              <BsFillXCircleFill
                color="var(--danger)"
                size={15}
                title="exclude"
              />
            </button>
          </div>
        ))}
      </Tags>
    </Container>
  );
};

export default TagSearch;
