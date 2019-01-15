/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint()
{

}

void main()
{
    char *videoMemory = (char *)0xB8000;
    *videoMemory = 'X';
}
