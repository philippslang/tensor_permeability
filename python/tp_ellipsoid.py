import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import json, sys


def ellipsoid(opts, n):

	def mvee(points, tol = 0.001):
		"""
		Finds the ellipse equation in "center form"
		(x-c).T * A * (x-c) = 1
		"""
		N, d = points.shape
		Q = np.column_stack((points, np.ones(N))).T
		err = tol+1.0
		u = np.ones(N)/N
		while err > tol:
			X = np.dot(np.dot(Q, np.diag(u)), Q.T)
			M = np.diag(np.dot(np.dot(Q.T, la.inv(X)), Q))
			jdx = np.argmax(M)
			step_size = (M[jdx]-d-1.0)/((d+1)*(M[jdx]-1.0))
			new_u = (1-step_size)*u
			new_u[jdx] += step_size
			err = la.norm(new_u-u)
			u = new_u
		c = np.dot(u,points)        
		A = la.inv(np.dot(np.dot(points.T, np.diag(u)), points)
				   - np.multiply.outer(c,c))/d
		return A, c

	pts = []
	for opt in opts:
		nppt = np.array(opt)
		pts.append(nppt)
		nppt = np.array(opt)*(-1.0)
		pts.append(nppt)
	points = np.array(pts)

	A, centroid = mvee(points)    
	U, D, V = la.svd(A)    
	rx, ry, rz = 1./np.sqrt(D)
	u, v = np.mgrid[0:2*np.pi:20j, -np.pi/2:np.pi/2:10j]

	def ellipse(u,v):
		x = rx*np.cos(u)*np.cos(v)
		y = ry*np.sin(u)*np.cos(v)
		z = rz*np.sin(v)
		return x,y,z

	E = np.dstack(ellipse(u,v))
	E = np.dot(E,V) + centroid
	x, y, z = np.rollaxis(E, axis = -1)

	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	ax.plot_surface(x, y, z, cstride = 1, rstride = 1, alpha = 0.05)
	for p in points:
		ax.plot([0, p[0]], [0, p[1]], [0, p[2]], color='blue', alpha=0.5, lw=3)
	ax.get_xaxis().set_ticks([])
	ax.set_xlabel('x')
	ax.get_yaxis().set_ticks([])
	ax.set_ylabel('y')
	ax.set_zticks([])
	ax.set_zlabel('z')
	plt.title(n)
	plt.show()


def ellipsoid_points(j):
	js = j['sampling regions']
	ons = {}
	for on in js:
		evals = np.array(js[on]['eigen values'])
		idcssort = np.argsort(evals)
		evecs = js[on]['eigen vectors']
		vmax = evals[2]
		for i in idcssort:
			sf = evals[i]/vmax
			for ie in range(3):
				evecs[i][ie] *= sf
		ons[on] = evecs
	return ons

	
if __name__ == '__main__':
	fname = 'results.json'
	if len(sys.argv) > 1:
		fname = sys.argv[1]
		if '.json' not in fname:
			fname += '.json'
	with open(fname, 'r') as f:
		j = json.load(f)
	ons = ellipsoid_points(j)
	for on in ons:
		ellipsoid(ons[on],on)