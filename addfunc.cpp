atom add(func f)
{
  atom sum=0;
  for (int i=0,i<8;i++)
    sum+=f.arg[i];
  return sum;
}
