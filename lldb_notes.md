
```bash
# To watch a specific memory address in LLDB, you can use the watchpoint set expression command followed by the memory address.
# For example, if you want to watch the memory address of the first element in the bytes array, you can use the following command in the LLDB console:
watchpoint set expression &bytes[0]

#Yes, you can set a watchpoint on a specific memory address using a literal value in LLDB. However, you should be very careful when doing this, as incorrect usage can lead to undefined behavior or crashes.
#Here's how you can do it:

watchpoint set expression -- (uint32_t*)0x12345678
```

```bash
#list watchpoint
watchpoint list

# verbose option
watchpoint list -v

#delete watchpoint
watchpoint delete 1

# delete all
watchpoint delete
```

- **Examine memory**: `memory read --size 4 --format x --count 1 0x12345678`

```bash
frame variable variable_name
p variable_name
```