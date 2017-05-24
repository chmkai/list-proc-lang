atom div(func f)
{
  int quo=0;
  if((f.arg(1)).rtype() == 'n'&&(f.arg(2)).rtype() == 'n')
    quo=f.arg(1)%f.arg(2);    
  atom x;
  x.setval(sum,'n');
  return x;
}
