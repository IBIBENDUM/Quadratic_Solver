bool request_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    assert(!(a_ptr == b_ptr));
    assert(!(a_ptr == c_ptr));
    assert(!(b_ptr == c_ptr));

    show_separator();
    printf("Введите коэффициенты через пробел:\n");

    if(read_coefs(a_ptr, b_ptr, c_ptr) != 3)
    {
        printf("Ошибка при вводе коэффициентов\n");
        return false; // TODO: true for an erroneous state? Weird choice I gotta say!
    }
    return true;

}
bool ask_for_continue(void)
{
    int ch;

    printf("Желаете продолжить? (Y для продолжения, что-то другое для выхода)\n");

    while (isspace(ch=getchar()))
        continue;

    skip_line();

    return (toupper(ch) == 'Y');
}


