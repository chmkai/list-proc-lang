atom add(func f)
{
  int sum=0;
  for (int i=1,i<9;i++)
    sum+=f.arg[i];
  atom x;
  x.setval(sum,'n');
  return x;
}
