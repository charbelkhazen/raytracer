void pars_fillMaterial(t_mat *mat, material_type type)
{
	if (type == MATTE_TYPE)
		mat_fillMatte(mat, 
}

int	pars_parseSphere(t_obj *obj, char *buf)
{
	t_vec	center;
	t_vec	color;
	double	diameter;
	material_type	mat_type; //TODO:can use mat instead
	t_shape shape;
	t_mat	mat;

	std_assert(buf != 0);
	mat_type = MATTE_TYPE;
	pars_skipWhiteSpace(&buf);
	if (pars_consume3Numbers(&center, &buf) || pars_consumeMandatoryWhiteSpace(&buf) 
		|| pars_consumeNumber(&diameter, &buf) || pars_consumeMandatoryWhiteSpace(&buf)
		|| pars_consume3Integers(&color, &buf))
		return (1);
	pars_skipWhiteSpace(&buf);
	if(*buf)
	{
		if (pars_consumeMaterial(&mat.mat_type, &buf)) 
			return (1);
		pars_skipWhiteSpace(&buf);
	}
	if(*buf)
		return (1);
	if (pars_checkColorRange(color) || diameter < 0)
		return (1);
	shape_fillSphere(&shape, center, diameter / 2.0);
	//TODO : SHOULD ADAPT TO CHOSEN MATERIAL!!!!!
	// if (mat.mat_type == ... -> else ...)
	mat_fillMatte(&mat, 0); // wrong assumes only matte
	obj_fillObj(obj, shape, mat, color);
	return (0);
}
