atom multiply(func f)
{
  int prod=1;
  for (int i=1,i<9;i++)
    if((f.arg(i)).rtype() == 'n')
      prod*=f.arg[i];
  atom x;
  x.setval(prod,'n');
  return x;
}
