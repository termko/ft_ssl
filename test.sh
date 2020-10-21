for f in /bin/*; do
	echo "$f md5";
  ./ft_ssl md5 "$f" > file1;
  openssl md5 "$f" > file2;
	diff file1 file2;
	echo "$f sha256";
  ./ft_ssl sha256 "$f" > file1;
  openssl sha256 "$f" > file2;
  diff file1 file2;
done
