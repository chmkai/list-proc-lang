atom subtract(func f)
{
  int diff=0;
  diff=f.arg[1]-f.arg[2];
  atom x;
  x.setval(diff,'n');
  return x;
}
