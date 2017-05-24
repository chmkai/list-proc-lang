atom subtract(func f)
{
  int sum=0;
  for (int i=2,i<9;i++)
    if((f.arg(i)).rtype() == 'n')
      sum+=f.arg(i);
  atom x;
  x.setval(arg[1]-sum,'n');
  return x;
}
