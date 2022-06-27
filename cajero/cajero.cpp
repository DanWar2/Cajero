#include <iostream>
#include <stdlib.h>
#include <string> //libreria usada para el manejo de strings y convertir strings int, float, double, etc y viceversas sto
#include <regex> //libreria usada para el uso de regex/ comprobaciones
#include <time.h> //libreria usada para llamar la hora del sistema

#include <windows.h> //trabajar consola en windows
#include <iomanip>

#include <conio.h>
#include <stdio.h>

#define colores SetConsoleTextAttribute

using namespace std;

//funcion gotoxy para posicionar el cursor en un punto especifico de la consola

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //identificador 
	COORD poss;	 //guardar coordenadas-define las coordenadas de una celda
	poss.X = x;
	poss.Y = y;

	SetConsoleCursorPosition(handle, poss);
}

//llamada a la funcion
void cuadro();
void cuadro2();

int main()
{
	char c;
	bool condicion = false, condicion2, condicion3, condicion4, condicion5;
	int random=0, opcion = 0, opcion2 = 0, opcion4 = 0, opcion5 = 0, columna = 0, columna2 = 0, columna3 = 0, columna4 = 0, servicio = 0, fila, fila2, filas = 5, n[5][8];		//cambiar el valor de la variable filas y las filas de n para aumentar el numero maximo de usuarios
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	string mostrar, nombre, password, password2, edad, saldo, saldo2, id, idPrueba, direccion, nombre1, opcionPrueba;
	string datos[5][5], transferencias[5][10], retiros[5][10], depositos[5][10], pagos[5][10];								//cambiar el valor de las filas para aumentar el numero total de usuarios (se debe cambiar a todas las tablas)
	regex comprobarOpc("[0-9]+"), comprobarNombre("^([A-Z¡…Õ”⁄—]{1}[a-z·ÈÌÛ˙Ò]+(\\s)?)+$"), comprobarEdad("[0-9]{2}"), comprobarSaldo("^[0-9]+([.][0-9]{1,2})?$");
	//llenado de la matriz datos con "-"
	for (int i = 0; i < filas; i++) //filas
	{
		for (int j = 0; j < 5; j++) //columnas
		{
			datos[i][j] = "-";
		}
	}
	//Llenado de tablas de historial con -
	for (int i = 0; i < filas; i++) //filas
	{
		for (int j = 0; j < 10; j++) //columnas
		{

			transferencias[i][j] = "-";
			depositos[i][j] = "-";
			retiros[i][j] = "-";
			pagos[i][j] = "-";
		}
	}
	//llenado de N
	for (int i = 0; i < filas; i++) //filas
	{
		int aux1 = 0, aux2 = 1;

		for (int j = 0; j < 4; j++) //columnas
		{
			n[i][aux1] = -1;
			n[i][aux2] = 0;
			aux1 += 2;
			aux2 += 2;
		}
	}

	do
	{
		system("cls");
		cuadro();
		colores(color, 11); 
		gotoxy(45, 4); cout << "Cajero  Automatico";
		colores(color, 14); 
		gotoxy(43, 9); cout << "Tu Banco de Confianza!";
		gotoxy(36, 13); cout << "Digite la opcion que desea realizar:\n";
		colores(color, 8);
		gotoxy(38, 15); cout << "1 - Registrarse";
		gotoxy(38, 16); cout << "2 - Ingresar en su cuenta";
		gotoxy(38, 17); cout << "  - Otro numero para salir del programa\n\n\t: ";
		colores(color, 15);
		getline(cin,opcionPrueba); 
		condicion = regex_match(opcionPrueba, comprobarOpc);
		if (condicion)
		{
			opcion = stoi(opcionPrueba);
			switch (opcion)
			{
			case 1:

				//ccomprobar si hay espacios disponibles
				for (int i = 0; i < filas; i++) //filas
				{
					if (datos[i][1] != "-") //condicion
					{
						condicion = false; //No enontro disponible
					}
					else
					{
						condicion = true; //Encontro disponible
						fila = i; //guardar la fila
						i = filas+1; //salir del bucle porque ya encontro una fila disponible
					}
				}

				if (condicion)
				{
					do
					{
						id = "";
						condicion2 = true;
						system("cls");
						do
						{
							system("cls");
							cuadro2();
							colores(color, 11);
							gotoxy(50, 4); cout << "Registro";
							colores(color, 15);
							gotoxy(6, 9); cout << "\tIngrese su nombre: ";
							getline(cin, nombre);
							condicion = regex_match(nombre, comprobarNombre);

							if (condicion)
							{
								if (nombre.size() > 2)
								{
									id = nombre[0];
									id += nombre[1];
									datos[fila][1] = nombre;
								}
								else
								{
									colores(color, 12);
									cout << "\n\t\t\t\t\t\t**Error: **\n\n\t\t\t\tEl nombre No Puede ser menor a 2 caracteres.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
									colores(color, 15);
									condicion = false;
									system("pause");
								}
							}
							else
							{

								colores(color, 12);
								gotoxy(6, 10); cout << "\n\t\t\t\t\t** Se genero un error: **\n\n\t\t\t\tEl nombre No debe quedar vacio\n\t\t\t\tEl nombre debe iniciar con mayuscula\n\t\t\t\tNo puede iniciar con un espacio\n\t\t\t\tNi debe contener numeros\n\t\t\t\tNo debe llevar mas de dos espacios entre palabras.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
								colores(color, 15);
								system("pause");
							}

						} while (condicion == false);

						do
						{
							system("cls");
							cuadro2();
							colores(color, 11);
							gotoxy(50, 4); cout << "Registro";
							colores(color, 8);
							gotoxy(8, 9); cout << "Nombre: " << datos[fila][1] << ".";
							colores(color, 15);
							gotoxy(8, 11); cout << "Ingrese su edad: ";
							getline(cin, edad);
							//validar que la edad sean numeros
							condicion = regex_match(edad, comprobarEdad);

							if (condicion)
							{
								if (stoi(edad) >= 18)
								{
									datos[fila][2] = edad;
									id += edad;
								}
								else
								{
									colores(color, 12);
									gotoxy(8, 14); cout << "\t\t   **La edad no puede ser menor a 18 ni mayor a 99**\n\n\t\t\t\t";
									condicion = false;
									colores(color, 15);
									system("pause");
								}

							}
							else
							{
								colores(color, 12);
								gotoxy(8, 14); cout << "\t\t   Error: *No pueden ir letras ni numeros negativos.* \n\t\t\t\t  *Solo son validas cantidades de dos digitos.* \n\t\t\t\t  *No utilice simbolos ni deje espacios en blanco.*\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
								colores(color, 15);
								system("pause");
							}

						} while (condicion == false);

						do
						{
							system("cls");
							condicion = true;
							cuadro2();
							colores(color, 11);
							gotoxy(50, 4); cout << "Registro";
							colores(color, 8);
							gotoxy(8, 9); cout << "Nombre: " << datos[fila][1] << ".";
							gotoxy(8, 10); cout << "Edad: " << datos[fila][2] << ".";
							colores(color, 15);
							gotoxy(8, 12); cout << "Ingrese una contrasenia no menor a 8 datos alfanumericos: ";
							getline(cin, password);

							if (password.size() > 8)
							{	
								colores(color, 8);
								gotoxy(8, 12); cout << "Ingrese una contrasenia no menor a 8 datos alfanumericos: ";
								colores(color, 15);
								cout << password;
								gotoxy(31, 15); cout << "\tVuelva a ingresar su contrasenia: ";
								getline(cin, password2);

								if (password != password2)
								{
									colores(color, 12);
									gotoxy(8, 18); cout << "\t\t\t **Error: Las contrasenias no coinciden.**\n\n\t\t\t\t\t**Vuelva a ingresarlas**\n\n\t\t\t\t";
									colores(color, 15);
									condicion = false;
									system("pause");
								}
								else
								{
									datos[fila][3] = password;
								}
							}
							else
							{
								colores(color, 12);
								gotoxy(8, 15); cout << "\t\t\t**Error: La contrasenia es muy corta.**\n\n\t\t\t\t\t**Vuelva a ingresarla.**\n\n\t\t\t\t";
								colores(color, 15);
								condicion = false;
								system("pause");
							}

						} while (condicion == false);

						do
						{
							system("cls");
							cuadro2();
							colores(color, 11);
							gotoxy(48, 4); cout << "Registro";
							colores(color, 8);
							gotoxy(8, 9); cout << "Nombre: " << datos[fila][1] << ".";
							gotoxy(8, 10); cout << "Edad: " << datos[fila][2] << ".";
							gotoxy(8, 11); cout << "Contrasenia: " << datos[fila][3] << ".";
							colores(color, 15);
							gotoxy(8, 13); cout << "Ingrese la cantidad de dinero con que iniciara su cuenta no menor a '$50': $ ";
							getline(cin, saldo);
							//validar que sean numeros
							condicion = regex_match(saldo, comprobarSaldo);

							if (condicion)
							{
								if (stod(saldo) >= 50)
								{
									datos[fila][4] = saldo;
								}
								else
								{
									do
									{
										system("cls");
										opcion4 = 0;
										cuadro2();
										colores(color, 11);
										gotoxy(48, 4); cout << "Registro";
										colores(color, 8);
										gotoxy(8, 9); cout << "Nombre: " << datos[fila][1] << ".";
										gotoxy(8, 10); cout << "Edad: " << datos[fila][2] << ".";
										gotoxy(8, 11); cout << "Contrasenia: " << datos[fila][3] << ".";
										colores(color, 15);
										gotoxy(8, 13); cout << "Ingrese la cantidad de dinero con que iniciara su cuenta no menor a '$50': $ " << saldo;
										colores(color, 12);
										gotoxy(8, 15); cout << "\t**Error: La cantidad para iniciar una cuenta no puede ser menor a $50**";
										condicion = false;
										colores(color, 8);
										gotoxy(12, 17); cout << "Ingrese 1 para intentarlo nuevamente";
										gotoxy(12, 18); cout << "Ingrese otro numero para cancelar la cracion de la cuenta y volver al menu anterior.\n\n\t:";
										colores(color, 15);
										getline(cin, opcionPrueba);
										condicion = regex_match(opcionPrueba, comprobarOpc);
										if (condicion)
										{
											opcion4 = stoi(opcionPrueba);
											if (opcion4 == 1)
											{
												condicion = false;
											}
											else
											{
												condicion = true;
												condicion2 = false;
												opcion4 = 1;
											}
										}
										else
										{
											colores(color, 12);
											cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
											gotoxy(8, 24); cout << "\t\t\t Vuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
											colores(color, 15);
											system("pause");
										}

									} while (opcion4==0);
								}
							}
							else
							{
								colores(color, 12);
								gotoxy(8, 15); cout << "\t**Error: No pueden ir letras, numeros negativos, mas de dos decimales.**\n\t\t\t No utilice simbolos ni deje espacios en blanco.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
								colores(color, 15);
								condicion = false;
								system("pause");
							}

						} while (condicion == false);

						if (condicion == true && condicion2 == true)
						{
							do
							{
								//la funcion srand sirve para asignarle una semilla/numero de inicio, al pasarle como parametro time 
								//este usa la hora del sistema para generar una semilla que proporcione un numero mas aleatorio 
								srand(time(0)); 
								random = (rand() % 90) + 10; //la funcion rand es la que se encarga de generar los "numeros aleatoriios" en un rango comenzando en 0
								idPrueba = id + to_string(random);
								condicion = true;

								for (int i = 0; i < filas; i++)
								{
									if (datos[i][0] == idPrueba)
									{
										condicion = false;
										i = filas + 1;
									}
								}

							} while (condicion==false);

							id += to_string(random);

							do
							{
								system("cls");
								cuadro2();
								colores(color, 11);
								gotoxy(50, 4); cout << "Registro";
								colores(color, 14);
								gotoxy(37, 9); cout << "** Verificacion de su cuenta **";
								colores(color, 15);
								gotoxy(8, 11); cout << "Su identificador de cuenta es: " + id + ". Por favor anote este dato es muy importante para";
								gotoxy(8, 12); cout << "acceder a su cuenta. A continuacion se muestran sus datos por favor revisarlos con cuidado.";
								datos[fila][0] = id;
								colores(color, 8);
								gotoxy(15, 14); cout << "Id de cuenta : " + datos[fila][0] + "";
								gotoxy(50, 14); cout << "Nombre: " + datos[fila][1] + "";
								gotoxy(15, 15); cout << "Edad: " + datos[fila][2] + "";
								gotoxy(50, 15); cout << "Contrasenia: " + datos[fila][3] + "";
								gotoxy(50, 16); cout << "Saldo de: $" << fixed << setprecision(2) << stod(datos[fila][4]);
								colores(color, 15);
								gotoxy(8, 18); cout << "Los datos ingresados son correctos? Digite:";
								colores(color, 8);
								gotoxy(12, 19); cout << "1 - Para si ";
								gotoxy(12, 20); cout << "2 - Para cancelar la creacion de la cuenta";
								gotoxy(12, 21); cout << "  - Otro numero para volver a llenar los datos.";
								gotoxy(8, 22); cout << ": ";
								colores(color, 15);
								getline(cin, opcionPrueba);
								condicion = regex_match(opcionPrueba, comprobarOpc);
								if (condicion)
								{
									opcion4 = stoi(opcionPrueba);

									if (opcion4 == 2)
									{
										opcion4 = 1;
										for (int i = 0; i < filas; i++)
										{
											datos[fila][i] = "-";
										}
									}
								}
								else
								{
									colores(color, 12);
									cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
									gotoxy(12, 25); cout << "\t\t\t* Vuelva a intentarlo utilizando numeros *\n\t\t\t\t  ";
									colores(color, 15);
									system("pause");

								}

							} while (condicion == false);
						}
						else
						{
							for (int i = 0; i < filas; i++)
							{
								datos[fila][i] = "-";
							}
						}

					} while (opcion4 != 1);

				}
				else
				{
					colores(color, 12);
					cout << "\n\n\t\t\t\t** No hay espacio para agregar mas datos. **\n\n\t\t\t\t   ";
					colores(color, 15);
					system("pause");
				}

				break;

			case 2:
				do
				{
					system("cls");
					id = "";
					condicion = false;
					cuadro2();
					colores(color, 11);
					gotoxy(50, 4); cout << "Ingresar";
					colores(color, 15);
					gotoxy(8, 9); cout << "Ingrese su identificador de la cuenta (id): ";
					getline(cin, id);
					//existe el id
					for (int i = 0; i < filas; i++)
					{
						if (datos[i][0] == id)
						{
							condicion = true;
							fila = i;
							i = filas+1;
						}
					}

					if (condicion)
					{
						do
						{
							password = "";
							condicion = true;
							system("cls");
							cuadro2();
							colores(color, 11);
							gotoxy(50, 4); cout << "Ingresar";
							colores(color, 8);
							gotoxy(8, 9); cout << "Su identificador de la cuenta (id) es : " << datos[fila][0] << endl;
							colores(color, 15);
							gotoxy(8, 11); cout << "Ingrese su contrasenia: ";
							getline(cin, password);
							if (password == datos[fila][3])
							{
								do
								{

									system("cls");
									cuadro();
									colores(color, 11);
									gotoxy(45, 4); cout << "Sistema de Cuentas";
									colores(color, 14);
									gotoxy(17, 9); cout << "Id: " << datos[fila][0] << ", Nombre: " << datos[fila][1] << ", Edad c. creo la cuenta: " << datos[fila][2] << ", Saldo actual $" << fixed << setprecision(2) << stod(datos[fila][4]);
									gotoxy(36, 13); cout << "Digite la opcion que desea realizar:\n";
									colores(color, 8);
									gotoxy(31, 15); cout << "1 - Retiro";
									gotoxy(31, 16); cout << "2 - Deposito";
									gotoxy(31, 17); cout << "3 - Pagos";
									gotoxy(50, 15); cout << "4 - Transferencias";
									gotoxy(50, 16); cout << "5 - Historial de la cuenta";
									gotoxy(50, 17); cout << "6 - Cambio de contrasenia";
									gotoxy(50, 18); cout << "  - Otro numero para cerrar sesion\n\n\t: ";
									colores(color, 15);
									getline(cin, opcionPrueba);
									condicion = regex_match(opcionPrueba, comprobarOpc);

									if (condicion)
									{
										opcion2 = stoi(opcionPrueba);
										switch (opcion2)
										{
										case 1:

											do
											{
												system("cls");
												cuadro();
												colores(color, 11);
												gotoxy(45, 4); cout << "Retiro de Dinero";
												colores(color, 14);
												gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
												gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser de $1)";
												colores(color, 15);
												gotoxy(8, 15); cout << "Ingrese la cantidad de dinero que desea retirar de su cuenta :  $ ";
												getline(cin, saldo);
												condicion = regex_match(saldo, comprobarSaldo);

												if (condicion)
												{
													if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
													{
														if (stod(saldo) != 0)
														{
															do
															{
																system("cls");
																cuadro();
																colores(color, 11);
																gotoxy(45, 4); cout << "Retiro de Dinero";
																colores(color, 14);
																gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																colores(color, 15);
																gotoxy(8, 13); cout << "Se hara un retiro de $ "; colores(color, 14); cout << saldo; colores(color, 15); cout << " desde su cuenta. ";
																cout << "Desea completar la accion?";
																colores(color, 8);
																gotoxy(12, 15); cout << "1 -Para si";
																gotoxy(12, 16); cout << "  -Otro numero para cancelar la operacion y volver al menu anterior\n\n\t: ";
																colores(color, 15);
																getline(cin, opcionPrueba);
																condicion = regex_match(opcionPrueba, comprobarOpc);
																if (condicion)
																{
																	opcion4 = stoi(opcionPrueba);

																	if (opcion4 == 1)
																	{
																		datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																		colores(color, 10);
																		gotoxy(10, 20); cout << "-----------------------------------------------------------------";
																		colores(color, 15);
																		gotoxy(8, 22); cout << "Su retiro se realizo con exito.\n\n\tSu nuevo saldo es de : $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\t\t\t\t";
																		colores(color, 15);
																		system("pause");
																		condicion4 = false;
																		//comprobar si hay espacios disponibles
																		for (int i = 0; i < 10; i++) //columna
																		{
																			if (retiros[fila][i] != "-") //condicion
																			{
																				condicion4 = false; //No encontro disponible
																			}
																			else
																			{
																				condicion4 = true; //Encontro disponible una columna
																				columna3 = i; //guardar la columna vacia que encontro
																				i = 10; //salir del bucle porque ya encontro una columna disponible
																			}
																		}
																		if (condicion4 == true)
																		{
																			n[fila][3] += 1;
																			retiros[fila][columna3] = "Retiro #" + to_string(n[fila][3]);
																			retiros[fila][columna3] += " fue de: -$" + saldo;
																		}
																		else
																		{
																			n[fila][2] += 1;

																			if (n[fila][2] > 9)
																			{
																				n[fila][2] = 0;
																			}

																			n[fila][3] += 1;
																			retiros[fila][n[fila][2]] = "Retiro #" + to_string(n[fila][3]);
																			retiros[fila][n[fila][2]] += " fue de: -$" + saldo;
																		}

																	}
																	condicion = true;
																}
																else
																{
																	colores(color, 12);
																	cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																	gotoxy(8, 20); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																}

															} while (regex_match(opcionPrueba, comprobarOpc) == false);

															
														}
														else
														{
															colores(color, 12);
															gotoxy(8, 17); cout << "\t\tNo se puede retirar el valor de $0. Intentelo nuevamente.**\n\n\t\t\t\t";
															colores(color, 15);
															system("pause");
															condicion = false;
														}
													}
													else
													{
														do
														{
															system("cls");
															cuadro();
															colores(color, 11);
															gotoxy(45, 4); cout << "Retiro de Dinero";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
															colores(color, 15);
															gotoxy(8, 15); cout << "Ingrese la cantidad de dinero que desea retirar de su cuenta :  $ " << saldo;
															colores(color, 12);
															gotoxy(8, 17); cout << "\t**Error: La cantidad es mayor que la de su saldo acual o la cuenta quedaria a 0**";
															colores(color, 8);
															gotoxy(12, 19); cout << "Ingrese 1 - Intentelo nuevamente. - Otro numero para salir. \n\n\t: ";
															colores(color, 15);
															getline(cin, opcionPrueba);
															condicion = regex_match(opcionPrueba, comprobarOpc);
															if (condicion)
															{
																opcion4 = stoi(opcionPrueba);

																if (opcion4 == 1)
																{
																	condicion = false;
																}
																else
																{
																	condicion = true;
																}
															}
															else
															{
																colores(color, 12);
																cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																gotoxy(15, 23); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
															}
														} while (regex_match(opcionPrueba, comprobarOpc)==false);

													}
												}
												else
												{
												
													colores(color, 12);
													gotoxy(8, 17); cout << "\t**Error: No pueden ir letras, numeros negativos, mas de dos decimales.**\n\t\t\t No utilice simbolos ni deje espacios en blanco.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
													colores(color, 15);
													system("pause");
													condicion = false;
												}

											} while (condicion == false);

											break;

										case 2:
											do
											{
												system("cls");
												cuadro();
												colores(color, 11);
												gotoxy(45, 4); cout << "Deposito de Dinero";
												colores(color, 14);
												gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
												colores(color, 15);
												gotoxy(8, 13); cout << "Ingrese la cantidad de dinero que desea depositar en su cuenta: $ ";
												getline(cin, saldo);
												condicion = regex_match(saldo, comprobarSaldo);

												if (condicion)
												{
													if (stod(saldo) > 0)
													{
														do
														{
															system("cls");
															cuadro();
															colores(color, 11);
															gotoxy(45, 4); cout << "Deposito de Dinero";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															colores(color, 15);
															gotoxy(8, 13); cout << "Se depositaran $ "; colores(color, 14); cout << saldo; colores(color, 15); cout << " a su cuenta. ";
															cout << "Desea completar la accion?";
															colores(color, 8);
															gotoxy(12, 15); cout << "1 -Para si";
															gotoxy(12, 16); cout << "  -Otro numero para cancelar la operacion y volver al menu anterior\n\n\t: ";
															colores(color, 15);
															getline(cin, opcionPrueba);
															condicion = regex_match(opcionPrueba, comprobarOpc);
															if (condicion)
															{
																opcion4 = stoi(opcionPrueba);

																if (opcion4 == 1)
																{

																	datos[fila][4] = to_string(stod(datos[fila][4]) + stod(saldo));
																	colores(color, 10);
																	gotoxy(10, 20); cout << "-----------------------------------------------------------------";
																	colores(color, 15);
																	gotoxy(8, 22); cout << "Su deposito se realizo con exito.\n\n\tSu nuevo saldo es de : $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion5 = false;
																	for (int i = 0; i < 10; i++) //columna
																	{
																		if (depositos[fila][i] != "-") //condicion
																		{
																			condicion5 = false; //No encontro disponible
																		}
																		else
																		{
																			condicion5 = true; //Encontro disponible una columna
																			columna4 = i; //guardar la columna vacia que encontro
																			i = 10; //salir del bucle porque ya encontro una columna disponible
																		}
																	}
																	if (condicion5 == true)
																	{
																		n[fila][5] += 1;
																		depositos[fila][columna4] = "Deposito #" + to_string(n[fila][5]);
																		depositos[fila][columna4] += " fue de: +$" + saldo;
																	}
																	else
																	{
																		n[fila][4] += 1;

																		if (n[fila][4] > 9)
																		{
																			n[fila][4] = 0;
																		}

																		n[fila][5] += 1;
																		depositos[fila][n[fila][4]] = "Deposito #" + to_string(n[fila][5]);
																		depositos[fila][n[fila][4]] += " fue de: +$" + saldo;
																	}

																}

																condicion = true;
															}
															else
															{
																colores(color, 12);
																cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																gotoxy(8, 20); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
															}

														} while (regex_match(opcionPrueba, comprobarOpc)==false);
													}
													else
													{
														colores(color, 12);
														gotoxy(8, 15); cout << "\t   ** Error: La cantidad es igual o menor a 0. Intentelo nuevamente. **\n\n\t\t\t\t";
														colores(color, 15);
														system("pause");
														condicion = false;
													}
												}
												else
												{
													colores(color, 12);
													gotoxy(8, 15); cout << "\t**Error: No pueden ir letras, numeros negativos, mas de dos decimales.**\n\t\t\t No utilice simbolos ni deje espacios en blanco.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
													colores(color, 15);
													system("pause");
													condicion = false;
												}

											} while (condicion == false);

											break;

										case 3:
											do
											{
												system("cls");
												cuadro();
												colores(color, 11);
												gotoxy(45, 4); cout << " Menu  de  Pagos";
												colores(color, 14);
												gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
												gotoxy(36, 13); cout << "Digite la opcion que desea realizar:\n";
												colores(color, 8);
												gotoxy(38, 15); cout << "1 - Pago del servicio de luz";
												gotoxy(38, 16); cout << "2 - Pago del servicio de agua";
												gotoxy(38, 17); cout << "3 - Pago del servicio de internet";
												gotoxy(38, 18); cout << "4 - Pago del servicio de cable";
												gotoxy(38, 19); cout << "  - Otro numero para volver. \n\n\t :";
												colores(color, 15);
												getline(cin, opcionPrueba);
												condicion = regex_match(opcionPrueba, comprobarOpc);
												if (condicion)
												{
													servicio = stoi(opcionPrueba);

													switch (servicio)
													{
													case 1:
														do 
														{
															system("cls");
															condicion2 = true;
															cuadro();
															colores(color, 11);
															gotoxy(47, 4); cout << "Pago  de  Luz.";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
															colores(color, 15);
															gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ ";
															getline(cin, saldo);

															condicion = regex_match(saldo, comprobarSaldo);

															if (condicion)
															{
																if (stod(saldo) != 0)
																{
																	if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
																	{

																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(47, 4); cout << "Pago  de  Luz.";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			colores(color, 8);
																			gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese el nombre del consumidor: ";
																			getline(cin, nombre1);
																			condicion = regex_match(nombre1, comprobarNombre);
																			//validar que el nombre sean letras

																			if (condicion)
																			{
																				if (nombre1.size() > 2)
																				{
																					do
																					{
																						system("cls");
																						cuadro();
																						colores(color, 11);
																						gotoxy(47, 4); cout << "Pago  de  Luz.";
																						colores(color, 14);
																						gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																						colores(color, 8);
																						gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																						gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																						colores(color, 15);
																						gotoxy(8, 16); cout << "Ingrese la direccion: ";
																						getline(cin, direccion);

																						if (direccion.size() >= 10)
																						{
																							do
																							{
																								system("cls");
																								cuadro();
																								colores(color, 11);
																								gotoxy(47, 4); cout << "Pago  de  Luz.";
																								colores(color, 14);
																								gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																								colores(color, 8);
																								gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																								gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																								gotoxy(8, 15); cout << "Ingrese la direccion: " << direccion;

																								colores(color, 15);
																								gotoxy(8, 17); cout << "Los datos ingresados son correctos? Digite:";
																								colores(color, 8);
																								gotoxy(12, 18); cout << "1 - Para si ";
																								gotoxy(12, 19); cout << "2 - Para volver a llenar los datos";
																								gotoxy(12, 20); cout << "  - Otro numero para volver al menu anterior.";
																								gotoxy(8, 22); cout << ": ";
																								colores(color, 15);
																								getline(cin, opcionPrueba);
																								condicion = regex_match(opcionPrueba, comprobarOpc);
																								if (condicion)
																								{
																									opcion4 = stoi(opcionPrueba);

																									switch (opcion4)
																									{
																									case 1:

																										system("cls");
																										cuadro2();
																										colores(color, 11);
																										gotoxy(47, 4); cout << "Pago  De  Luz.";
																										colores(color, 14);

																										datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																										colores(color, 14);
																										gotoxy(8, 9); cout << "*Realizo el pago por la cantidad de: $" << fixed << setprecision(2) << stod(saldo) << " por el servicio de luz*";
																										colores(color, 8);
																										gotoxy(8, 11); cout << "Nombre del consumidor: " << nombre1;
																										gotoxy(8, 12); cout << "Direccion: " << direccion;
																										colores(color, 10);
																										gotoxy(10, 14); cout << "-----------------------------------------------------------------";
																										colores(color, 15);
																										gotoxy(8, 16); cout << "Su saldo actual ahora es de $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\n\t\t\t\t";
																										colores(color, 15);
																										system("pause");
																										//comprobar si hay espacios disponibles
																										for (int i = 0; i < 10; i++) //columna
																										{
																											if (pagos[fila][i] != "-") //condicion
																											{
																												condicion4 = false; //No encontro disponible
																											}
																											else
																											{
																												condicion4 = true; //Encontro disponible una columna
																												columna3 = i; //guardar la columna vacia que encontro
																												i = 10; //salir del bucle porque ya encontro una columna disponible
																											}
																										}
																										if (condicion4 == true)
																										{
																											n[fila][9] += 1;
																											pagos[fila][columna3] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][columna3] += " fue de: -$" + saldo;
																										}
																										else
																										{
																											n[fila][8] += 1;

																											if (n[fila][8] > 9)
																											{
																												n[fila][8] = 0;
																											}

																											n[fila][9] += 1;
																											pagos[fila][n[fila][8]] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][n[fila][8]] += " fue de: -$" + saldo;
																										}
																										condicion = true;

																										break;

																									case 2:
																										condicion = true;
																										condicion2 = false;
																										break;

																									default:
																										condicion = true;
																										break;
																									}
																								}
																								else
																								{
																									colores(color, 12);
																									cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																									gotoxy(12, 25); cout << "\t\t\t* Vuelva a intentarlo utilizando numeros *\n\t\t\t\t  ";
																									colores(color, 15);
																									system("pause");

																								}

																							} while (regex_match(opcionPrueba, comprobarOpc) == false);

																						}
																						else
																						{
																							colores(color, 12);
																							gotoxy(0, 19); cout << "\t\t\t\t\t\t**Error: **\n\t\t\t\t No Puede ser menor a 10 caracteres.\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																							colores(color, 15);
																							system("pause");
																						}

																					} while (direccion.size() < 10);
																				}
																				else
																				{
																					colores(color, 12);
																					cout << "\n\t\t\t\t\t\t**Error: **\n\n\t\t\t\tEl nombre No Puede ser menor a 2 caracteres.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																					colores(color, 15);
																					condicion = false;
																					system("pause");
																				}


																			}
																			else {
																				colores(color, 12);
																				gotoxy(6, 17); cout << "\t\t\t\t\t** Se genero un error: **\n\t\t\t\tEl nombre No debe quedar vacio\n\t\t\t\tEl nombre debe iniciar con mayuscula\n\t\t\t\tNo puede iniciar con un espacio\n\t\t\t\tNi debe contener numeros\n\t\t\t\tNo debe llevar mas de dos espacios entre palabras.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																				condicion = false;
																			}

																		} while (condicion == false);
																	}
																	else
																	{
																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(47, 4); cout << "Pago  de  Luz.";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 12);
																			gotoxy(8, 17); cout << "\t**Error: La cantidad es mayor que la de su saldo actual o la cuenta quedaria a 0**";
																			colores(color, 8);
																			gotoxy(12, 19); cout << "Ingrese 1 para volver a intentar u otro numero para salir.\n\n\t\t: ";
																			colores(color, 15);
																			getline(cin, opcionPrueba);
																			condicion = regex_match(opcionPrueba, comprobarOpc);
																			if (condicion)
																			{
																				opcion5 = stoi(opcionPrueba);

																				if (opcion5 == 1)
																				{
																					condicion = false;
																				}
																				else
																				{
																					condicion = true;
																				}
																			}
																			else
																			{
																				colores(color, 12);
																				cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																				gotoxy(8, 24); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																			}

																		} while (regex_match(opcionPrueba, comprobarOpc) == false);
																	}
																}
																else
																{
																	colores(color, 12);
																	gotoxy(8, 17); cout << "\tNo se puede realizar un pago por el valor de $0. Intentelo nuevamente.**\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion = false;
																}
															}
															else {
																colores(color, 12);
																gotoxy(8, 17); cout << "\t\t*Error: no puede ingresar letras y numeros negativos*\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
																condicion = false;
															}

														} while (condicion == false || condicion2 == false);

														break;

													case 2:
														
														do 
														{
															system("cls");
															condicion2 = true;
															cuadro();
															colores(color, 11);
															gotoxy(47, 4); cout << "Pago  de  Agua";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
															colores(color, 15);
															gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ ";
															getline(cin, saldo);

															condicion = regex_match(saldo, comprobarSaldo);

															if (condicion)
															{
																if (stod(saldo) != 0)
																{
																	if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
																	{

																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(47, 4); cout << "Pago  de  Agua";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			colores(color, 8);
																			gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese el nombre del consumidor: ";
																			getline(cin, nombre1);
																			condicion = regex_match(nombre1, comprobarNombre);
																			//validar que el nombre sean letras


																			if (condicion)
																			{

																				if (nombre1.size() > 2)
																				{
																					do
																					{
																						system("cls");
																						cuadro();
																						colores(color, 11);
																						gotoxy(47, 4); cout << "Pago  de  Agua";
																						colores(color, 14);
																						gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																						colores(color, 8);
																						gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																						gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																						colores(color, 15);
																						gotoxy(8, 16); cout << "Ingrese la direccion: ";
																						getline(cin, direccion);

																						if (direccion.size() >= 10)
																						{

																							do
																							{
																								system("cls");
																								cuadro();
																								colores(color, 11);
																								gotoxy(47, 4); cout << "Pago  de  Agua";
																								colores(color, 14);
																								gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																								colores(color, 8);
																								gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																								gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																								gotoxy(8, 15); cout << "Ingrese la direccion: " << direccion;

																								colores(color, 15);
																								gotoxy(8, 17); cout << "Los datos ingresados son correctos? Digite:";
																								colores(color, 8);
																								gotoxy(12, 18); cout << "1 - Para si ";
																								gotoxy(12, 19); cout << "2 - Para volver a llenar los datos";
																								gotoxy(12, 20); cout << "  - Otro numero para volver al menu anterior.";
																								gotoxy(8, 22); cout << ": ";
																								colores(color, 15);
																								getline(cin, opcionPrueba);
																								condicion = regex_match(opcionPrueba, comprobarOpc);
																								if (condicion)
																								{
																									opcion4 = stoi(opcionPrueba);

																									switch (opcion4)
																									{
																									case 1:

																										system("cls");
																										cuadro2();
																										colores(color, 11);
																										gotoxy(47, 4); cout << "Pago  De  Agua";
																										colores(color, 14);

																										datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																										colores(color, 14);
																										gotoxy(8, 9); cout << "*Realizo el pago por la cantidad de: $" << fixed << setprecision(2) << stod(saldo) << " por el servicio de agua*";
																										colores(color, 8);
																										gotoxy(8, 11); cout << "Nombre del consumidor: " << nombre1;
																										gotoxy(8, 12); cout << "Direccion: " << direccion;
																										colores(color, 10);
																										gotoxy(10, 14); cout << "-----------------------------------------------------------------";
																										colores(color, 15);
																										gotoxy(8, 16); cout << "Su saldo actual ahora es de $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\n\t\t\t\t";
																										colores(color, 15);
																										system("pause");
																										//comprobar si hay espacios disponibles
																										for (int i = 0; i < 10; i++) //columna
																										{
																											if (pagos[fila][i] != "-") //condicion
																											{
																												condicion4 = false; //No encontro disponible
																											}
																											else
																											{
																												condicion4 = true; //Encontro disponible una columna
																												columna3 = i; //guardar la columna vacia que encontro
																												i = 10; //salir del bucle porque ya encontro una columna disponible
																											}
																										}
																										if (condicion4 == true)
																										{
																											n[fila][9] += 1;
																											pagos[fila][columna3] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][columna3] += " fue de: -$" + saldo;
																										}
																										else
																										{
																											n[fila][8] += 1;

																											if (n[fila][8] > 9)
																											{
																												n[fila][8] = 0;
																											}

																											n[fila][9] += 1;
																											pagos[fila][n[fila][8]] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][n[fila][8]] += " fue de: -$" + saldo;
																										}
																										condicion = true;

																										break;

																									case 2:
																										condicion = true;
																										condicion2 = false;
																										break;

																									default:
																										condicion = true;
																										break;
																									}

																								}
																								else
																								{
																									colores(color, 12);
																									cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																									gotoxy(12, 25); cout << "\t\t\t* Vuelva a intentarlo utilizando numeros *\n\t\t\t\t  ";
																									colores(color, 15);
																									system("pause");

																								}

																							} while (regex_match(opcionPrueba, comprobarOpc) == false);

																						}
																						else
																						{
																							colores(color, 12);
																							gotoxy(0, 19); cout << "\t\t\t\t\t\t**Error: **\n\t\t\t\t No Puede ser menor a 10 caracteres.\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																							colores(color, 15);
																							system("pause");
																						}

																					} while (direccion.size() < 10);
																				}
																				else
																				{
																					colores(color, 12);
																					cout << "\n\t\t\t\t\t\t**Error: **\n\n\t\t\t\tEl nombre No Puede ser menor a 2 caracteres.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																					colores(color, 15);
																					condicion = false;
																					system("pause");
																				}


																			}
																			else {
																				colores(color, 12);
																				gotoxy(6, 17); cout << "\t\t\t\t\t** Se genero un error: **\n\t\t\t\tEl nombre No debe quedar vacio\n\t\t\t\tEl nombre debe iniciar con mayuscula\n\t\t\t\tNo puede iniciar con un espacio\n\t\t\t\tNi debe contener numeros\n\t\t\t\tNo debe llevar mas de dos espacios entre palabras.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																				condicion = false;
																			}

																		} while (condicion == false);
																	}
																	else
																	{
																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(47, 4); cout << "Pago  de  Agua";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 12);
																			gotoxy(8, 17); cout << "\t**Error: La cantidad es mayor que la de su saldo actual o la cuenta quedaria a 0**";
																			colores(color, 8);
																			gotoxy(12, 19); cout << "Ingrese 1 para volver a intentar u otro numero para salir.\n\n\t\t: ";
																			colores(color, 15);
																			getline(cin, opcionPrueba);
																			condicion = regex_match(opcionPrueba, comprobarOpc);
																			if (condicion)
																			{
																				opcion5 = stoi(opcionPrueba);

																				if (opcion5 == 1)
																				{
																					condicion = false;
																				}
																				else
																				{
																					condicion = true;
																				}
																			}
																			else
																			{
																				colores(color, 12);
																				cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																				gotoxy(8, 24); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																			}

																		} while (regex_match(opcionPrueba, comprobarOpc) == false);
																	}
																}
																else
																{
																	colores(color, 12);
																	gotoxy(8, 17); cout << "\tNo se puede realizar un pago por el valor de $0. Intentelo nuevamente.**\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion = false;
																}
															}
															else {
																colores(color, 12);
																gotoxy(8, 17); cout << "\t\t*Error: no puede ingresar letras y numeros negativos*\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
																condicion = false;
															}

														} while (condicion == false || condicion2 == false);

														break;

													case 3:
														
														do 
														{
															system("cls");
															condicion2 = true;
															cuadro();
															colores(color, 11);
															gotoxy(45, 4); cout << "Pago de Internet";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
															colores(color, 15);
															gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ ";
															getline(cin, saldo);

															condicion = regex_match(saldo, comprobarSaldo);

															if (condicion)
															{
																if (stod(saldo) != 0)
																{
																	if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
																	{

																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(45, 4); cout << "Pago de Internet";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			colores(color, 8);
																			gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese el nombre del consumidor: ";
																			getline(cin, nombre1);
																			condicion = regex_match(nombre1, comprobarNombre);
																			//validar que el nombre sean letras


																			if (condicion)
																			{

																				if (nombre1.size() > 2)
																				{
																					do
																					{
																						system("cls");
																						cuadro();
																						colores(color, 11);
																						gotoxy(45, 4); cout << "Pago de Internet";
																						colores(color, 14);
																						gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																						colores(color, 8);
																						gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																						gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																						colores(color, 15);
																						gotoxy(8, 16); cout << "Ingrese la direccion: ";
																						getline(cin, direccion);

																						if (direccion.size() >= 10)
																						{

																							do
																							{
																								system("cls");
																								cuadro();
																								colores(color, 11);
																								gotoxy(45, 4); cout << "Pago de Internet";
																								colores(color, 14);
																								gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																								colores(color, 8);
																								gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																								gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																								gotoxy(8, 15); cout << "Ingrese la direccion: " << direccion;

																								colores(color, 15);
																								gotoxy(8, 17); cout << "Los datos ingresados son correctos? Digite:";
																								colores(color, 8);
																								gotoxy(12, 18); cout << "1 - Para si ";
																								gotoxy(12, 19); cout << "2 - Para volver a llenar los datos";
																								gotoxy(12, 20); cout << "  - Otro numero para volver al menu anterior.";
																								gotoxy(8, 22); cout << ": ";
																								colores(color, 15);
																								getline(cin, opcionPrueba);
																								condicion = regex_match(opcionPrueba, comprobarOpc);
																								if (condicion)
																								{
																									opcion4 = stoi(opcionPrueba);

																									switch (opcion4)
																									{
																									case 1:

																										system("cls");
																										cuadro2();
																										colores(color, 11);
																										gotoxy(45, 4); cout << "Pago de Internet";
																										colores(color, 14);
																										datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																										colores(color, 14);
																										gotoxy(8, 9); cout << "*Realizo el pago por la cantidad de: $" << fixed << setprecision(2) << stod(saldo) << " por el servicio de internet*";
																										colores(color, 8);
																										gotoxy(8, 11); cout << "Nombre del consumidor: " << nombre1;
																										gotoxy(8, 12); cout << "Direccion: " << direccion;
																										colores(color, 10);
																										gotoxy(10, 14); cout << "-----------------------------------------------------------------";
																										colores(color, 15);
																										gotoxy(8, 16); cout << "Su saldo actual ahora es de $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\n\t\t\t\t";
																										colores(color, 15);
																										system("pause");

																										//comprobar si hay espacios disponibles
																										for (int i = 0; i < 10; i++) //columna
																										{
																											if (pagos[fila][i] != "-") //condicion
																											{
																												condicion4 = false; //No encontro disponible
																											}
																											else
																											{
																												condicion4 = true; //Encontro disponible una columna
																												columna3 = i; //guardar la columna vacia que encontro
																												i = 10; //salir del bucle porque ya encontro una columna disponible
																											}
																										}
																										if (condicion4 == true)
																										{
																											n[fila][9] += 1;
																											pagos[fila][columna3] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][columna3] += " fue de: -$" + saldo;
																										}
																										else
																										{
																											n[fila][8] += 1;

																											if (n[fila][8] > 9)
																											{
																												n[fila][8] = 0;
																											}

																											n[fila][9] += 1;
																											pagos[fila][n[fila][8]] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][n[fila][8]] += " fue de: -$" + saldo;
																										}
																										condicion = true;

																										break;

																									case 2:
																										condicion = true;
																										condicion2 = false;
																										break;

																									default:
																										condicion = true;
																										break;
																									}
																								}
																								else
																								{
																									colores(color, 12);
																									cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																									gotoxy(12, 25); cout << "\t\t\t* Vuelva a intentarlo utilizando numeros *\n\t\t\t\t  ";
																									colores(color, 15);
																									system("pause");

																								}

																							} while (regex_match(opcionPrueba, comprobarOpc) == false);

																						}
																						else
																						{
																							colores(color, 12);
																							gotoxy(0, 19); cout << "\t\t\t\t\t\t**Error: **\n\t\t\t\t No Puede ser menor a 10 caracteres.\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																							colores(color, 15);
																							system("pause");
																						}

																					} while (direccion.size() < 10);
																				}
																				else
																				{
																					colores(color, 12);
																					cout << "\n\t\t\t\t\t\t**Error: **\n\n\t\t\t\tEl nombre No Puede ser menor a 2 caracteres.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																					colores(color, 15);
																					condicion = false;
																					system("pause");
																				}


																			}
																			else {
																				colores(color, 12);
																				gotoxy(6, 17); cout << "\t\t\t\t\t** Se genero un error: **\n\t\t\t\tEl nombre No debe quedar vacio\n\t\t\t\tEl nombre debe iniciar con mayuscula\n\t\t\t\tNo puede iniciar con un espacio\n\t\t\t\tNi debe contener numeros\n\t\t\t\tNo debe llevar mas de dos espacios entre palabras.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																				condicion = false;
																			}

																		} while (condicion == false);
																	}
																	else
																	{
																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(45, 4); cout << "Pago de Internet";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 12);
																			gotoxy(8, 17); cout << "\t**Error: La cantidad es mayor que la de su saldo actual o la cuenta quedaria a 0**";
																			colores(color, 8);
																			gotoxy(12, 19); cout << "Ingrese 1 para volver a intentar u otro numero para salir.\n\n\t\t: ";
																			colores(color, 15);
																			getline(cin, opcionPrueba);
																			condicion = regex_match(opcionPrueba, comprobarOpc);
																			if (condicion)
																			{
																				opcion5 = stoi(opcionPrueba);

																				if (opcion5 == 1)
																				{
																					condicion = false;
																				}
																				else
																				{
																					condicion = true;
																				}
																			}
																			else
																			{
																				colores(color, 12);
																				cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																				gotoxy(8, 24); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																			}

																		} while (regex_match(opcionPrueba, comprobarOpc) == false);
																	}
																}
																else
																{
																	colores(color, 12);
																	gotoxy(8, 17); cout << "\tNo se puede realizar un pago por el valor de $0. Intentelo nuevamente.**\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion = false;
																}
															}
															else {
																colores(color, 12);
																gotoxy(8, 17); cout << "\t\t*Error: no puede ingresar letras y numeros negativos*\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
																condicion = false;
															}

														} while (condicion == false || condicion2 == false);

														break;

													case 4:
														
														do 
														{
															system("cls");
															condicion2 = true;
															cuadro();
															colores(color, 11);
															gotoxy(46, 4); cout << "Pago  de  Cable";
															colores(color, 14);
															gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
															gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
															colores(color, 15);
															gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ ";
															getline(cin, saldo);

															condicion = regex_match(saldo, comprobarSaldo);

															if (condicion)
															{
																if (stod(saldo) != 0)
																{
																	if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
																	{

																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(46, 4); cout << "Pago  de  Cable";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			colores(color, 8);
																			gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese el nombre del consumidor: ";
																			getline(cin, nombre1);
																			condicion = regex_match(nombre1, comprobarNombre);
																			//validar que el nombre sean letras


																			if (condicion)
																			{

																				if (nombre1.size() > 2)
																				{
																					do
																					{
																						system("cls");
																						cuadro();
																						colores(color, 11);
																						gotoxy(46, 4); cout << "Pago  de  Cable";
																						colores(color, 14);
																						gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																						colores(color, 8);
																						gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																						gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																						colores(color, 15);
																						gotoxy(8, 16); cout << "Ingrese la direccion: ";
																						getline(cin, direccion);

																						if (direccion.size() >= 10)
																						{

																							do
																							{
																								system("cls");
																								cuadro();
																								colores(color, 11);
																								gotoxy(46, 4); cout << "Pago  de  Cable";
																								colores(color, 14);
																								gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																								colores(color, 8);
																								gotoxy(8, 13); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																								gotoxy(8, 14); cout << "Ingrese el nombre del consumidor: " << nombre1;
																								gotoxy(8, 15); cout << "Ingrese la direccion: " << direccion;

																								colores(color, 15);
																								gotoxy(8, 17); cout << "Los datos ingresados son correctos? Digite:";
																								colores(color, 8);
																								gotoxy(12, 18); cout << "1 - Para si ";
																								gotoxy(12, 19); cout << "2 - Para volver a llenar los datos";
																								gotoxy(12, 20); cout << "  - Otro numero para volver al menu anterior.";
																								gotoxy(8, 22); cout << ": ";
																								colores(color, 15);
																								getline(cin, opcionPrueba);
																								condicion = regex_match(opcionPrueba, comprobarOpc);
																								if (condicion)
																								{
																									opcion4 = stoi(opcionPrueba);

																									switch (opcion4)
																									{
																									case 1:

																										system("cls");
																										cuadro2();
																										colores(color, 11);
																										gotoxy(46, 4); cout << "Pago  de  Cable";
																										colores(color, 14);

																										datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																										colores(color, 14);
																										gotoxy(8, 9); cout << "*Realizo el pago por la cantidad de: $" << fixed << setprecision(2) << stod(saldo) << " por el servicio de cable*";
																										colores(color, 8);
																										gotoxy(8, 11); cout << "Nombre del consumidor: " << nombre1;
																										gotoxy(8, 12); cout << "Direccion: " << direccion;
																										colores(color, 10);
																										gotoxy(10, 14); cout << "-----------------------------------------------------------------";
																										colores(color, 15);
																										gotoxy(8, 16); cout << "Su saldo actual ahora es de $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\n\t\t\t\t";
																										colores(color, 15);
																										system("pause");
																										//comprobar si hay espacios disponibles
																										for (int i = 0; i < 10; i++) //columna
																										{
																											if (pagos[fila][i] != "-") //condicion
																											{
																												condicion4 = false; //No encontro disponible
																											}
																											else
																											{
																												condicion4 = true; //Encontro disponible una columna
																												columna3 = i; //guardar la columna vacia que encontro
																												i = 10; //salir del bucle porque ya encontro una columna disponible
																											}
																										}
																										if (condicion4 == true)
																										{
																											n[fila][9] += 1;
																											pagos[fila][columna3] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][columna3] += " fue de: -$" + saldo;
																										}
																										else
																										{
																											n[fila][8] += 1;

																											if (n[fila][8] > 9)
																											{
																												n[fila][8] = 0;
																											}

																											n[fila][9] += 1;
																											pagos[fila][n[fila][8]] = "Retiro #" + to_string(n[fila][9]);
																											pagos[fila][n[fila][8]] += " fue de: -$" + saldo;
																										}
																										condicion = true;

																										break;

																									case 2:
																										condicion = true;
																										condicion2 = false;
																										break;

																									default:
																										condicion = true;
																										break;
																									}

																								}
																								else
																								{
																									colores(color, 12);
																									cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																									gotoxy(12, 25); cout << "\t\t\t* Vuelva a intentarlo utilizando numeros *\n\t\t\t\t  ";
																									colores(color, 15);
																									system("pause");

																								}

																							} while (regex_match(opcionPrueba, comprobarOpc) == false);

																						}
																						else
																						{
																							colores(color, 12);
																							gotoxy(0, 19); cout << "\t\t\t\t\t\t**Error: **\n\t\t\t\t No Puede ser menor a 10 caracteres.\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																							colores(color, 15);
																							system("pause");
																						}

																					} while (direccion.size() < 10);
																				}
																				else
																				{
																					colores(color, 12);
																					cout << "\n\t\t\t\t\t\t**Error: **\n\n\t\t\t\tEl nombre No Puede ser menor a 2 caracteres.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																					colores(color, 15);
																					condicion = false;
																					system("pause");
																				}


																			}
																			else {
																				colores(color, 12);
																				gotoxy(6, 17); cout << "\t\t\t\t\t** Se genero un error: **\n\t\t\t\tEl nombre No debe quedar vacio\n\t\t\t\tEl nombre debe iniciar con mayuscula\n\t\t\t\tNo puede iniciar con un espacio\n\t\t\t\tNi debe contener numeros\n\t\t\t\tNo debe llevar mas de dos espacios entre palabras.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																				condicion = false;
																			}

																		} while (condicion == false);
																	}
																	else
																	{
																		do
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(46, 4); cout << "Pago  de  Cable";
																			colores(color, 14);
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																			colores(color, 15);
																			gotoxy(8, 15); cout << "Ingrese la cantidad a pagar : $ " << saldo;
																			colores(color, 12);
																			gotoxy(8, 17); cout << "\t**Error: La cantidad es mayor que la de su saldo actual o la cuenta quedaria a 0**";
																			colores(color, 8);
																			gotoxy(12, 19); cout << "Ingrese 1 para volver a intentar u otro numero para salir.\n\n\t\t: ";
																			colores(color, 15);
																			getline(cin, opcionPrueba);
																			condicion = regex_match(opcionPrueba, comprobarOpc);
																			if (condicion)
																			{
																				opcion5 = stoi(opcionPrueba);

																				if (opcion5 == 1)
																				{
																					condicion = false;
																				}
																				else
																				{
																					condicion = true;
																				}
																			}
																			else
																			{
																				colores(color, 12);
																				cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																				gotoxy(8, 24); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																				colores(color, 15);
																				system("pause");
																			}

																		} while (regex_match(opcionPrueba, comprobarOpc) == false);
																	}
																}
																else
																{
																	colores(color, 12);
																	gotoxy(8, 17); cout << "\tNo se puede realizar un pago por el valor de $0. Intentelo nuevamente.**\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion = false;
																}
															}
															else {
																colores(color, 12);
																gotoxy(8, 17); cout << "\t\t*Error: no puede ingresar letras y numeros negativos*\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
																condicion = false;
															}

														} while (condicion == false || condicion2 == false);

														break;
													}

												}
												else
												{
													colores(color, 12);
													cout << "\n\t\t**Error: no puede ingresar letras para seleccionar una opcion del menu.**\n\t\t\t\t Vuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
													colores(color, 15);
													system("pause");

												}

											} while (condicion == false || servicio > 0 && servicio < 5);

											break;

										case 4:

											do
											{
												id = "";
												opcion4 = 0;
												system("cls");
												cuadro2();
												colores(color, 11);
												gotoxy(46, 4); cout << "Transferencias.";
												colores(color, 15);
												gotoxy(8, 9); cout << "Ingrese el identificador de la cuenta (id) a la que va a transferir: ";
												getline(cin, id);
												//existe el id
												for (int i = 0; i < filas; i++)
												{
													if (datos[i][0] == id)
													{
														condicion = true;
														fila2 = i;
														i = filas+1;
													}
													else
													{
														condicion = false;
													}
												}

												if (condicion == true) {
													do
													{
														system("cls");
														cuadro();
														colores(color, 11);
														gotoxy(46, 4); cout << "Transferencias.";
														colores(color, 14);
														gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
														gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
														colores(color, 15);
														gotoxy(8, 15); cout << "Ingrese la cantidad de dinero que desea transferir a la cuenta de " << datos[fila2][1] << " (" << datos[fila2][0] << ")" << " \n\n\t: $ ";
														getline(cin, saldo);
														condicion = regex_match(saldo, comprobarSaldo);

														if (condicion)
														{
															if (stod(saldo) != 0)
															{
																if (stod(saldo) < stod(datos[fila][4]) && (stod(datos[fila][4])) - stod(saldo) >= 1)
																{
																	system("cls");
																	cuadro();
																	colores(color, 11);
																	gotoxy(46, 4); cout << "Transferencias.";
																	colores(color, 14);
																	gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																	gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																	colores(color, 8);
																	gotoxy(8, 15); cout << "Ingrese la cantidad de dinero que desea transferir a la cuenta de " << datos[fila2][1] << " (" << datos[fila2][0] << ")" << " \n\n\t: $ ";
																	colores(color,15);
																	cout << saldo;
																	gotoxy(8, 19); cout << "Ingrese la cantidad nuevamente para confirmar: $ ";
																	getline(cin, saldo2);
																	condicion = regex_match(saldo2, comprobarSaldo);

																	if (condicion)
																	{
																		if (saldo == saldo2)
																		{
																			system("cls");
																			cuadro();
																			colores(color, 11);
																			gotoxy(46, 4); cout << "Transferencias.";
																			colores(color, 14);
																			datos[fila][4] = to_string(stod(datos[fila][4]) - stod(saldo));
																			datos[fila2][4] = to_string(stod(datos[fila2][4]) + stod(saldo));
																			gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																			gotoxy(8, 13); cout << "Transfirio la cantidad de $: " << fixed << setprecision(2) << saldo << " para la cuenta de " << datos[fila2][0] << "\n ";
																			colores(color, 10);
																			gotoxy(10, 15); cout << "-----------------------------------------------------------------";
																			colores(color, 15);
																			gotoxy(8, 17); cout << "Su nuevo saldo es de : $" << fixed << setprecision(2) << stod(datos[fila][4]) << "\n\n\t\t\t\t";
																			colores(color, 15);
																			system("pause");
																			condicion2 = false;

																			//comprobar si hay espacios disponibles
																			for (int i = 0; i < 10; i++) //columna
																			{
																				if (transferencias[fila][i] != "-") //condicion
																				{
																					condicion2 = false; //No enontro disponible
																				}
																				else
																				{
																					condicion2 = true; //Encontro disponible
																					columna = i; //guardar la fila
																					i = 10; //salir del bucle porque ya encontro una fila disponible
																				}
																			}

																			for (int i = 0; i < 10; i++) //columnas
																			{
																				if (transferencias[fila2][i] != "-") //condicion
																				{
																					condicion3 = false; //No enontro disponible
																				}
																				else
																				{
																					condicion3 = true; //Encontro disponible
																					columna2 = i; //guardar la columna
																					i = 10; //salir del bucle porque ya encontro una fila disponible
																				}

																			}

																			if (condicion2 == true)
																					{
																				n[fila][1] += 1;
																				transferencias[fila][columna] = "Transaccion #" + to_string(n[fila][1]);
																				transferencias[fila][columna] += " fue de: -$" + saldo;
																			}
																			else
																			{
																				n[fila][0] += 1;
																				if (n[fila][0] > 9)
																				{
																					n[fila][0] = 0;
																				}

																				n[fila][1] += 1;
																				transferencias[fila][n[fila][0]] = "Transaccion #" + to_string(n[fila][1]);
																				transferencias[fila][n[fila][0]] += " fue de: -$" + saldo;
																			}

																			if (condicion3 == true)
																			{
																				n[fila2][1] += 1;
																				transferencias[fila2][columna2] = "Transaccion #" + to_string(n[fila2][1]);
																				transferencias[fila2][columna2] += " fue de: +$" + saldo;
																			}
																			else
																			{
																				n[fila2][0] += 1;
																				if (n[fila2][0] > 9)
																				{
																					n[fila2][0] = 0;
																				}
																				n[fila2][1] += 1;
																				transferencias[fila2][n[fila2][0]] = "Transaccion #" + to_string(n[fila2][1]);
																				transferencias[fila2][n[fila2][0]] += " fue de: +$" + saldo;
																			}
																			condicion = true;
																		}
																		else
																		{
																			colores(color, 12);
																			gotoxy(8, 21); cout << "\t\t**Error: Las cantidades no coinciden. Vuelva a ingresarlas**\n\n\t\t\t\t";
																			colores(color, 15);
																			system("pause");
																			condicion = false;
																		}
																	}
																	else
																	{
																		colores(color, 12);
																		gotoxy(8, 21); cout << "\t**Error: No pueden ir letras, numeros negativos, mas de dos decimales.**\n\t\t\t No utilice simbolos ni deje espacios en blanco.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
																		colores(color, 15);
																		system("pause");
																		condicion = false;
																	}
																}
																else
																{
																	do
																	{
																		system("cls");
																		cuadro();
																		colores(color, 11);
																		gotoxy(46, 4); cout << "Transferencias.";
																		colores(color, 14);
																		gotoxy(31, 9); cout << "Id: " << datos[fila][0] << ", Nombre : " << datos[fila][1] << " y Saldo actual: $" << fixed << setprecision(2) << stod(datos[fila][4]) << endl;
																		gotoxy(8, 13); cout << "\t*(Nota: la cuenta no puede quedarse a 0, el valor min de su saldo debe ser $1)";
																		colores(color, 15);
																		gotoxy(8, 15); cout << "Ingrese la cantidad de dinero que desea transferir a la cuenta de " << datos[fila2][1] << " (" << datos[fila2][0] << ")" << " \n\n\t: $ " << saldo;
																		colores(color, 12);
																		gotoxy(12, 19); cout << "**Error: La cantidad es mayor que la de su saldo acual o la cuenta quedaria a 0.**";
																		colores(color, 8);
																		gotoxy(12, 21); cout << "Ingrese 1-Intentarlo nuevamente -Otro numero para salir : ";
																		colores(color, 15);
																		getline(cin, opcionPrueba);
																		condicion = regex_match(opcionPrueba, comprobarOpc);

																		if (condicion)
																		{
																			opcion4 = stoi(opcionPrueba);

																			if (opcion4 == 1)
																			{
																				condicion = false;
																				opcion4 = 0;
																			}
																			else
																			{
																				condicion = true;
																			}
																		}
																		else
																		{
																			colores(color, 12);
																			cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																			gotoxy(8, 24); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																			colores(color, 15);
																			system("pause");
																		}

																	} while (regex_match(opcionPrueba, comprobarOpc)==false);
																}
															}
															else
															{
																colores(color, 12);
																gotoxy(8, 19); cout << "\tNo se puede hacer una transferencia con el valor de $0. Intentelo nuevamente.\n\n\t\t\t\t";
																colores(color, 15);
																system("pause");
																condicion = false;
															}

														}
														else
														{
															colores(color, 12);
															gotoxy(8, 19); cout << "\t**Error: No pueden ir letras, numeros negativos, mas de dos decimales.**\n\t\t\t No utilice simbolos ni deje espacios en blanco.\n\n\t\t\t\t\t**Intentelo nuevamente.**\n\n\t\t\t\t";
															colores(color, 15);
															system("pause");
															condicion = false;
														}

													} while (condicion == false);
												}
												else {
													do
													{
														system("cls");
														cuadro2();
														colores(color, 11);
														gotoxy(50, 4); cout << "Ingresar";
														colores(color, 15);
														gotoxy(8, 9); cout << "Ingrese su identificador de la cuenta (id): " << id;
														colores(color, 12);
														gotoxy(8, 11); cout << "\t\t**No se encontro ninguna cuenta con ese id.**";
														colores(color, 8);
														gotoxy(12, 13); cout << "Ingrese 1 - Para volver a intentanlo - Otro numero para regrese al menu anterior\n\n\t: ";
														colores(color, 15);
														getline(cin, opcionPrueba);
														condicion = regex_match(opcionPrueba, comprobarOpc);
														if (condicion)
														{
															opcion4 = stoi(opcionPrueba);
														}
														else
														{
															colores(color, 12);
															cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
															gotoxy(24, 19); cout << "\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
															colores(color, 15);
															system("pause");
														}

													} while (regex_match(opcionPrueba, comprobarOpc) == false);
												}

											} while (opcion4==1);

											break;

										case 5:
											do
											{
												opcion4 = 1;
												system("cls");
												cuadro();
												colores(color, 11);
												gotoxy(45, 4); cout << "Menu Del Historial";
												colores(color, 14);
												gotoxy(34, 9); cout << "Observe el Movimiento de su Cuenta.";
												gotoxy(36, 13); cout << "Digite la opcion que desea realizar:\n";
												colores(color, 8);
												gotoxy(39, 15); cout << "1 - Transferencias";
												gotoxy(39, 16); cout << "2 - Pagos";
												gotoxy(39, 17); cout << "3 - Retiros";
												gotoxy(39, 18); cout << "4 - Deposito";
												gotoxy(39, 19); cout << "  - Otro numero para volver.\n\n\t:";
												colores(color, 15);
												getline(cin, opcionPrueba);
												condicion = regex_match(opcionPrueba, comprobarOpc);
												if (condicion)
												{
													opcion4 = stoi(opcionPrueba);
													switch (opcion4)
													{
													case 1:
														system("cls");
														mostrar = "";
														cuadro2();
														colores(color, 11);
														gotoxy(41, 4); cout << "Historial de Transacciones";
														colores(color, 15); 
														for (int i = 0; i < 10; i++)
														{
															mostrar += "\t" + transferencias[fila][i] + "\n";

														}
														colores(color, 14);
														gotoxy(8, 9); cout << "Sus ultimas 10 transferencias fueron:";
														colores(color, 8);
														gotoxy(0, 11); cout << mostrar << "\n\n\t\t\t\t";
														colores(color, 15);
														system("pause");
														break;

													case 2:
														system("cls");
														mostrar = "";
														cuadro2();
														colores(color, 11);
														gotoxy(45, 4); cout << "Historial de Pagos";
														colores(color, 15);
														for (int i = 0; i < 10; i++)
														{
															mostrar += "\t" + pagos[fila][i] + "\n";
														}
														colores(color, 14);
														gotoxy(8, 9); cout << "Sus ultimas 10 pagos fueron:";
														colores(color, 8);
														gotoxy(0, 11); cout << mostrar << "\n\n\t\t\t\t";
														colores(color, 15);
														system("pause");
														break;
													case 3:
														system("cls");
														mostrar = "";
														cuadro2();
														colores(color, 11);
														gotoxy(44, 4); cout << "Historial de Retiros";
														colores(color, 15);
														for (int i = 0; i < 10; i++)
														{
															mostrar += "\t" + retiros[fila][i] + "\n";
														}
														colores(color, 14);
														gotoxy(8, 9); cout << "Sus ultimas 10 retiros fueron:";
														colores(color, 8);
														gotoxy(0, 11); cout << mostrar << "\n\n\t\t\t\t";
														colores(color, 15);
														system("pause");
														break;

													case 4:
														system("cls");
														mostrar = "";
														cuadro2();
														colores(color, 11);
														gotoxy(43, 4); cout << "Historial de Depositos";
														colores(color, 15);
														for (int i = 0; i < 10; i++)
														{
															mostrar += "\t" + depositos[fila][i] + "\n";
														}
														colores(color, 14);
														gotoxy(8, 9); cout << "Sus ultimas 10 depositos fueron:";
														colores(color, 8);
														gotoxy(0, 11); cout << mostrar << "\n\n\t\t\t\t";
														colores(color, 15);
														system("pause");
														break;
													}

												}
												else
												{
													colores(color, 12);
													cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*\n\n\t\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
													colores(color, 15);
													system("pause");

												}

											} while (opcion4 > 0 && opcion4 < 5);

											break;

										case 6:
											
											do
											{
												system("cls");
												password2 = "";
												cuadro2();
												colores(color, 11);
												gotoxy(43, 4); cout << "Cambio de contrasenia.";
												colores(color, 15);
												gotoxy(8, 9); cout << "Ingrese su contrasenia actual: ";
												getline(cin, password);
												if (password == datos[fila][3])
												{
													do
													{
														system("cls");
														condicion = true;
														cuadro2();
														colores(color, 11);
														gotoxy(43, 4); cout << "Cambio de contrasenia.";
														colores(color, 8);
														gotoxy(8, 9); cout << "Contrasenia actual: " << datos[fila][3];
														colores(color, 15);
														gotoxy(8, 11); cout << "Ingrese una nueva contrasenia no menor a 8 caracteres: " ;
														getline(cin, password);

														if (password.size() > 8)
														{
															if (password != datos[fila][3])
															{
																gotoxy(23, 13); cout << "Vuelva a ingresar su nueva contrasenia: ";
																getline(cin, password2);

																if (password != password2)
																{
																	colores(color, 12);
																	cout << "\n\t\t\t**Error: Las contrasenias no coinciden. Vuelva a ingresarlas**\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																	condicion = false;
																}
																else
																{
																	datos[fila][3] = password;
																	colores(color, 10);
																	gotoxy(10, 15); cout << "-----------------------------------------------------------------";
																	colores(color, 15);
																	cout << "\n\n\t\tLa contrasenia se cambio con exito.\n\n\n\t\t\t\t";
																	colores(color, 15);
																	system("pause");
																}
															}
															else
															{
																do
																{
																	system("cls");
																	cuadro2();
																	colores(color, 11);
																	gotoxy(43, 4); cout << "Cambio de contrasenia.";
																	colores(color, 8);
																	gotoxy(8, 9); cout << "Contrasenia actual: " << datos[fila][3];
																	colores(color, 15);
																	gotoxy(8, 11); cout << "Ingrese una nueva contrasenia no menor a 8 caracteres: " << password;
																	colores(color, 12);
																	cout << "\n\n\t\t**Error: La contrasenia es identica a la contrasenia actual. Vuelva a ingresarla**\n\n\t\t\t\t";
																	colores(color, 15);
																	gotoxy(8, 15); cout << "Aun desea cambiar su contrasenia? ";
																	colores(color, 8);
																	gotoxy(12, 17); cout << "Ingrese 1-Intentarlo nuevamente -Otro cancelar el cambio y volver al menu anterior\n\n\t: ";
																	colores(color, 15);
																	getline(cin, opcionPrueba);
																	condicion = regex_match(opcionPrueba, comprobarOpc);

																	if (condicion)
																	{
																		opcion4 = stoi(opcionPrueba);

																		if (opcion4 == 1)
																		{
																			condicion = false;
																		}
																		else
																		{
																			condicion = true;
																			password2 = datos[fila][3];
																		}
																	}
																	else
																	{
																		colores(color, 12);
																		cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
																		gotoxy(8, 23); cout << "\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
																		colores(color, 15);
																		system("pause");
																	}

																} while (regex_match(opcionPrueba, comprobarOpc)==false);

															}
														}
														else
														{
															colores(color, 12);
															cout << "\n\t\t\tError: La contrasenia es muy corta. Vuelva a ingresarla.**\n\n\t\t\t\t";
															colores(color, 15);
															system("pause");
															condicion = false;
														}

													} while (condicion == false);
												}
												else
												{
													colores(color, 12);
													cout << "\n\t\t\t**Error: La contrasenia no coincide. Vuelva a ingresarla.**\n\n\t\t\t\t";
													colores(color, 15);
													system("pause");
												}

											} while (password2 != datos[fila][3]);

											break;

										default:

											colores(color, 12);
											cout << "\n\t\tCerrando sesion";
											for (int i = 0; i < 4; i++)
											{
												cout << ".";
												Sleep(700);
											}
											cout << "\n\n";
											colores(color, 15);

											break;
										}
									}
									else
									{
										colores(color, 12);
										cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*\n\n\t\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
										colores(color, 15);
										condicion = false;
										opcion2 = 1;
										system("pause");
									}

								} while (opcion2 >= 1 && opcion2 < 7);

								condicion = true;
							}
							else
							{
								do
								{
									system("cls");
									cuadro2();
									colores(color, 11);
									gotoxy(50, 4); cout << "Ingresar";
									colores(color, 8);
									gotoxy(8, 9); cout << "Su identificador de la cuenta (id) es : " << datos[fila][0] << endl;
									colores(color, 15);
									gotoxy(8, 11); cout << "Ingrese su contrasenia: " << password;
									colores(color, 12);
									gotoxy(8, 13); cout << "\t\t\t\t**Error: Contrasenia incorrecta.**\n\n\t\t\t\t";
									colores(color, 8);
									gotoxy(12, 15); cout << "Ingrese 1 para intentarlo nuevamente";
									gotoxy(12, 16); cout << "Ingrese otro numero para volver al menu anterior.\n\n\t:";
									colores(color, 15);
									getline(cin, opcionPrueba);
									condicion = regex_match(opcionPrueba, comprobarOpc);
									if (condicion)
									{
										opcion4 = stoi(opcionPrueba);

										if (opcion4 == 1)
										{
											condicion = false;
										}
										else
										{
											condicion = true;
										}
									}
									else
									{
										colores(color, 12);
										cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
										gotoxy(8, 22); cout << "\t\t\t Vuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
										colores(color, 15);
										system("pause");
									}
								} while (regex_match(opcionPrueba, comprobarOpc)==false);
							}

						} while (condicion == false);

						opcion4 = 0;
					}
					else
					{
						do
						{
							system("cls");
							cuadro2();
							colores(color, 11);
							gotoxy(50, 4); cout << "Ingresar";
							colores(color, 15);
							gotoxy(8, 9); cout << "Ingrese su identificador de la cuenta (id): " << id;
							colores(color, 12);
							gotoxy(8, 11); cout << "\t\t**No se encontro ninguna cuenta con ese id.**";
							colores(color, 8);
							gotoxy(12, 13); cout << "Ingrese 1 - Para volver a intentanlo  - Otro numero para regrese al menu anterior.\n\n\t: ";
							colores(color, 15);
							getline(cin, opcionPrueba);
							condicion = regex_match(opcionPrueba, comprobarOpc);
							if (condicion)
							{
								opcion4 = stoi(opcionPrueba);
							}
							else
							{
								colores(color, 12);
								cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*";
								gotoxy(24, 19); cout << "\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
								colores(color, 15);
								system("pause");

							}
						} while (condicion==false);
					}

				} while (opcion4 == 1);

				break;
			case 320:
				system("cls");
				mostrar = "";
				for (int i = 0; i < filas; i++)
				{
					mostrar += "\n\tId :" + datos[i][0] + ", Nombre:" + datos[i][1] + ", Edad:" + datos[i][2] + ", Contrasenia:" + datos[i][3] + "; Saldo: $" + datos[i][4] + "\n\t";
				}

				cout << mostrar << endl;
				system("pause");

				break;

			default:
				colores(color, 12);
				cout << "\n\n\t\tSaliendo del programa";
				for (int i = 0; i < 3; i++)
				{
					cout << ".";
					Sleep(1000);
				}
				colores(color, 15);
				system("cls");

				break;
			}
		}
		else
		{
			colores(color, 12);
			cout << "\n\t*Error: Solo digite un numero para elegir la opcion. No utilice letras, simbolos u espacios.*\n\n\t\t\t\tVuelva a intentarlo utilizando numeros.\n\n\t\t\t\t";
			condicion = false;
			colores(color, 15);
			system("pause");
		}
	} while (opcion == 1 || opcion == 2 || opcion == 320 || condicion == false);

	return 0;
}

void cuadro() {

	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //identificador

	for (int x = 4; x <= 104; x++)
	{
		colores(color, 34);
		gotoxy(x, 1); cout << "*";
		gotoxy(x, 7); cout << "*";
		gotoxy(x, 11); cout << "*";
		gotoxy(x, 28); cout << "*";
	}
	for (int y = 1; y < 29; y++)
	{
		colores(color, 34);
		gotoxy(3, y); cout << "*";
		gotoxy(4, y); cout << "*";
		gotoxy(104, y); cout << "*";
		gotoxy(105, y); cout << "*";
	}

	colores(color, 1);
	gotoxy(38, 3); cout << "--------------------------------";
	gotoxy(22, 4); cout << "===============|";
	colores(color, 1);
	gotoxy(70, 4); cout << "|===============";
	gotoxy(38, 5); cout << "--------------------------------";
	colores(color, 15);

	return;
}

void cuadro2() {

	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int x = 4; x <= 104; x++)
	{
		colores(color, 34);
		gotoxy(x, 1); cout << "*";
		gotoxy(x, 7); cout << "*";
		gotoxy(x, 28); cout << "*";
	}
	for (int y = 1; y < 29; y++)
	{
		colores(color, 34);
		gotoxy(3, y); cout << "*";
		gotoxy(4, y); cout << "*";
		gotoxy(104, y); cout << "*";
		gotoxy(105, y); cout << "*";
	}

	colores(color, 1);
	gotoxy(38, 3); cout << "--------------------------------";
	gotoxy(22, 4); cout << "===============|";
	colores(color, 1);
	gotoxy(70, 4); cout << "|===============";
	gotoxy(38, 5); cout << "--------------------------------";
	colores(color, 15);

	return;
}