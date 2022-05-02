const reg = new RegExp(/^(\s*|\d+)$/);

export const isInteger = (str: string): boolean => {
  return reg.test(str);
};
