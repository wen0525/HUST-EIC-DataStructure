//Î±Âë
Status Concat(HString &T, HString s1, HString s2)
{
	if (T.ch)
		free(T.ch);
	if (!(T.ch = (char*)malloc((s1.length + s2.length) * sizeof(char))))
		exit(OVERFLOW);
	T.length = s1.length + s2.length;
	for(int i = 0; i < s1.length; i++)
		*(T.ch + i) = *(s1.ch + i);
	for(int j = 0; j < s2.length; j++)
		*(T.ch + s1.length + j) = *(s2.ch + j);
	return OK;
 }//Concat
