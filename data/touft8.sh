for file in *.cpp; do
	iconv -f gb2312 -t utf-8 "$file" -o "${file%.cpp}.cpp"
done
