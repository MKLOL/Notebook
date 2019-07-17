#define BUFFER_SIZE 1234
char buff[BUFFER_SIZE];
int buffIt;
inline int getNumber() {
  int ret = 0;
  while (buff[buffIt] < '0' || buff[buffIt] > '9')
    if (++buffIt == BUFFER_SIZE)
      fread(buff, BUFFER_SIZE, 1, stdin), buffIt = 0;
  while (buff[buffIt] >= '0' && buff[buffIt] <= '9') {
    ret = ret * 10 + buff[buffIt] - '0';
    if (++buffIt == BUFFER_SIZE) {
      buffIt = 0; fread(buff, BUFFER_SIZE, 1, stdin);
    }
  }
  return ret;
}
for(int i=1;i<=M;++i) {
  if(!getline(cin, s)) break;
  if (s == "") { --i; continue; }
  stringstream ss; ss << s;
  int x; while(ss >> x) { g[i].push_back(x+M+1); }
}
