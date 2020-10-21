for f in /bin/*; do
  ./ft_ssl md5 "$f" > file1;
  openssl md5 "$f" > file2;
	diff file1 file2;
  ./ft_ssl sha256 "$f" > file1;
  openssl sha256 "$f" > file2;
  diff file1 file2;
done
