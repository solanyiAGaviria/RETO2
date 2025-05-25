import random
import string
from datetime import datetime, timedelta

# Datos base
departamento = "Antioquia"
municipios = ["Medellin", "Rionegro", "Envigado", "Itagui", "Bello"]
tipos = ["casa", "casa barrio", "apartamento"]
metodos_pago = ["PSE", "TCredito"]
amenidades_list = ["ascensor", "piscina", "aire acondicionado", "caja fuerte", "parqueadero", "patio", "wifi", "tv", "lavadora", "bbq"]
anotaciones = [
    "Tiene parqueadero?", "Puedo llevar mascota?", "Hay aire acondicionado?", 
    "Se permite fumar?", "Tiene wifi?", "Incluye desayuno?", 
    "Hay vigilancia?", "Esta cerca del metro?", "Tiene cocina?", 
    "Es zona segura?"
]
nombres = ["Juan", "Pedro", "Maria", "Ana", "Luis", "Laura", "Carlos", "Jorge", "Daniela", "Camilo",
           "Felipe", "Natalia", "Sofia", "Andres", "Paula", "Diego", "Luisa", "Esteban", "Valentina", "Sebastian"]

# Direcciones
direcciones = [f"Calle {i} #{random.randint(1, 100)}-{random.randint(1, 100)}" for i in range(1, 101)]

# ALOJAMIENTOS
alojamientos = ["id_alojamiento;nombre;departamento;municipio;tipo;direccion;precio_noche;amenidades"]
alojamientos_ids = []
for i in range(1000, 1030):
    nombre = f"Alojamiento_{i}"
    mun = random.choice(municipios)
    tipo = random.choice(tipos)
    direccion = random.choice(direcciones)
    precio = random.randint(25000, 150000)
    amenidades = ",".join(random.sample(amenidades_list, k=random.randint(3, 6)))
    alojamientos.append(f"{i};{nombre};{departamento};{mun};{tipo};{direccion};{precio};{amenidades}")
    alojamientos_ids.append(str(i))

# ANFITRIONES
anfitriones = ["cedula;nombre;clave;antiguedad_meses;calificacion;alojamientos"]
anfitrion_cedulas = [f"{100000000 + i}" for i in range(1, 31)]
for cedula in anfitrion_cedulas:
    nombre = random.choice(nombres)
    clave = ''.join(random.choices(string.ascii_letters + string.digits, k=10))
    antiguedad = random.randint(1, 60)
    calificacion = round(random.uniform(0.0, 5.0), 1)
    num_alojamientos = random.randint(1, 3)
    aloj_asignados = random.sample(alojamientos_ids, k=num_alojamientos)
    anfitriones.append(f"{cedula};{nombre};{clave};{antiguedad};{calificacion};{','.join(aloj_asignados)}")

# HUÉSPEDES
huespedes = ["cedula;nombre;clave;calificacion"]
huesped_cedulas = [f"{200000000 + i}" for i in range(1, 31)]
for cedula in huesped_cedulas:
    nombre = random.choice(nombres)
    clave = ''.join(random.choices(string.ascii_letters + string.digits, k=7))
    calificacion = round(random.uniform(0.0, 5.0), 1)
    huespedes.append(f"{cedula};{nombre};{clave};{calificacion}")

# RESERVAS
reservas = ["codigo_reserva;cedula_huesped;id_alojamiento;fecha_pago;metodo_pago;fecha_inicio;fecha_fin;pregunta_cliente"]
base_date = datetime.strptime("01/05/2025", "%d/%m/%Y")
reservas_por_alojamiento = {}
reservas_por_huesped = {}
reserva_id = 1

# 1. Asegurar que cada alojamiento tenga al menos una reserva
alojamientos_por_usar = alojamientos_ids.copy()
random.shuffle(alojamientos_por_usar)

for id_aloj in alojamientos_por_usar:
    cedula = random.choice(huesped_cedulas)
    fecha_inicio = base_date + timedelta(days=random.randint(0, 30))
    duracion = random.randint(1, 4)
    fecha_fin = fecha_inicio + timedelta(days=duracion)
    fecha_pago = fecha_inicio - timedelta(days=random.randint(1, 3))
    metodo = random.choice(metodos_pago)
    pregunta = random.choice(anotaciones)
    codigo = f"RSV{reserva_id:04d}"
    reservas.append(f"{codigo};{cedula};{id_aloj};{fecha_pago.strftime('%d/%m/%Y')};{metodo};{fecha_inicio.strftime('%d/%m/%Y')};{fecha_fin.strftime('%d/%m/%Y')};{pregunta}")
    reservas_por_alojamiento.setdefault(id_aloj, []).append((fecha_inicio, fecha_fin))
    reservas_por_huesped.setdefault(cedula, []).append((fecha_inicio, fecha_fin))
    reserva_id += 1

# 2. Crear más reservas adicionales si se desea
for _ in range(30):
    cedula = random.choice(huesped_cedulas)
    id_aloj = random.choice(alojamientos_ids)

    intentos = 0
    max_intentos = 10

    while intentos < max_intentos:
        fecha_inicio = base_date + timedelta(days=random.randint(0, 90))
        duracion = random.randint(1, 5)
        fecha_fin = fecha_inicio + timedelta(days=duracion)

        colision_aloj = any(not (fecha_fin <= fi or fecha_inicio >= ff) for (fi, ff) in reservas_por_alojamiento.get(id_aloj, []))
        colision_huesped = any(not (fecha_fin <= fi or fecha_inicio >= ff) for (fi, ff) in reservas_por_huesped.get(cedula, []))

        if not colision_aloj and not colision_huesped:
            reservas_por_alojamiento.setdefault(id_aloj, []).append((fecha_inicio, fecha_fin))
            reservas_por_huesped.setdefault(cedula, []).append((fecha_inicio, fecha_fin))
            fecha_pago = fecha_inicio - timedelta(days=random.randint(1, 5))
            metodo = random.choice(metodos_pago)
            pregunta = random.choice(anotaciones)
            codigo_reserva = f"RSV{reserva_id:04d}"
            reservas.append(f"{codigo_reserva};{cedula};{id_aloj};{fecha_pago.strftime('%d/%m/%Y')};{metodo};{fecha_inicio.strftime('%d/%m/%Y')};{fecha_fin.strftime('%d/%m/%Y')};{pregunta}")
            reserva_id += 1
            break
        intentos += 1

# Guardar archivos
file_paths = {
    "anfitriones.txt": anfitriones,
    "huespedes.txt": huespedes,
    "alojamientos.txt": alojamientos,
    "reservas.txt": reservas,
    "historico.txt": [""]  # archivo vacío
}

for filename, lines in file_paths.items():
    with open(filename, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

# Verificación robusta
ids_usados = {line.split(";")[2] for line in reservas[1:]}  # omitir cabecera
ids_faltantes = sorted(set(alojamientos_ids) - ids_usados)

print(f"IDs de alojamiento sin reservas: {ids_faltantes}")
print(f"Total sin uso: {len(ids_faltantes)}")
print("Archivos generados en el directorio actual.")
