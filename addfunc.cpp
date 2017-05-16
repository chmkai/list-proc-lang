atom add(func f)
{
  int sum=0;
  for (int i=0,i<8;i++)
    sum+=f.arg[i];
  atom x;
  x.setval(sum,'n');
  return x;
}
