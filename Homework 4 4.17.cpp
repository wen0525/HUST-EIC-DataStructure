//Î±Âë
Status Replace(String &S, String T, String V)
{
	for (i = 1; i <= Strlen(S) - Strlen(T) + 1; i++)
		if (!StrCompare(SubString(S, i, Strlen(T)), T))
		{
			StrAssign(head, SubString(S, 1, i - 1));
			StrAssign(tail, SubString(S, i + Strlen(T), Strlen(S) - i - Strlen(T) + 1));
			StrAssign(S, Concat(head, V));
			StrAssign(S, Concat(S, tail));
			i += Strlen(V);
		}
	return OK;
}//Replace
