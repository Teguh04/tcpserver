PGDMP         7    
            w            serial     11.2 (Ubuntu 11.2-1.pgdg16.04+1)     11.2 (Ubuntu 11.2-1.pgdg16.04+1)     X           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                       false            Y           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                       false            Z           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                       false            [           1262    17148    serial    DATABASE     x   CREATE DATABASE serial WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'en_US.UTF-8' LC_CTYPE = 'en_US.UTF-8';
    DROP DATABASE serial;
             postgres    false            �            1259    18717    line    TABLE     �   CREATE TABLE public.line (
    id bigint NOT NULL,
    w1 bigint NOT NULL,
    w2 bigint NOT NULL,
    r double precision NOT NULL,
    template bigint NOT NULL
);
    DROP TABLE public.line;
       public         postgres    false            �            1259    18715    line_id_seq    SEQUENCE     t   CREATE SEQUENCE public.line_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 "   DROP SEQUENCE public.line_id_seq;
       public       postgres    false    198            \           0    0    line_id_seq    SEQUENCE OWNED BY     ;   ALTER SEQUENCE public.line_id_seq OWNED BY public.line.id;
            public       postgres    false    197            �            1259    17149 
   serialport    TABLE     L   CREATE TABLE public.serialport (
    data character varying(50) NOT NULL
);
    DROP TABLE public.serialport;
       public         postgres    false            �            1259    19012 	   way_point    TABLE     �   CREATE TABLE public.way_point (
    id bigint NOT NULL,
    w bigint NOT NULL,
    latitude double precision NOT NULL,
    longitude double precision NOT NULL,
    template bigint NOT NULL
);
    DROP TABLE public.way_point;
       public         postgres    false            �            1259    19010    way_point_id_seq    SEQUENCE     y   CREATE SEQUENCE public.way_point_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 '   DROP SEQUENCE public.way_point_id_seq;
       public       postgres    false    200            ]           0    0    way_point_id_seq    SEQUENCE OWNED BY     E   ALTER SEQUENCE public.way_point_id_seq OWNED BY public.way_point.id;
            public       postgres    false    199            �
           2604    18720    line id    DEFAULT     b   ALTER TABLE ONLY public.line ALTER COLUMN id SET DEFAULT nextval('public.line_id_seq'::regclass);
 6   ALTER TABLE public.line ALTER COLUMN id DROP DEFAULT;
       public       postgres    false    197    198    198            �
           2604    19015    way_point id    DEFAULT     l   ALTER TABLE ONLY public.way_point ALTER COLUMN id SET DEFAULT nextval('public.way_point_id_seq'::regclass);
 ;   ALTER TABLE public.way_point ALTER COLUMN id DROP DEFAULT;
       public       postgres    false    200    199    200            S          0    18717    line 
   TABLE DATA               7   COPY public.line (id, w1, w2, r, template) FROM stdin;
    public       postgres    false    198   F       Q          0    17149 
   serialport 
   TABLE DATA               *   COPY public.serialport (data) FROM stdin;
    public       postgres    false    196   c       U          0    19012 	   way_point 
   TABLE DATA               I   COPY public.way_point (id, w, latitude, longitude, template) FROM stdin;
    public       postgres    false    200   �       ^           0    0    line_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.line_id_seq', 179, true);
            public       postgres    false    197            _           0    0    way_point_id_seq    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.way_point_id_seq', 29, true);
            public       postgres    false    199            �
           2606    18722    line line_pkey 
   CONSTRAINT     L   ALTER TABLE ONLY public.line
    ADD CONSTRAINT line_pkey PRIMARY KEY (id);
 8   ALTER TABLE ONLY public.line DROP CONSTRAINT line_pkey;
       public         postgres    false    198            �
           2606    19017    way_point way_point_pkey 
   CONSTRAINT     V   ALTER TABLE ONLY public.way_point
    ADD CONSTRAINT way_point_pkey PRIMARY KEY (id);
 B   ALTER TABLE ONLY public.way_point DROP CONSTRAINT way_point_pkey;
       public         postgres    false    200            S      x������ � �      Q      x������ � �      U      x������ � �     