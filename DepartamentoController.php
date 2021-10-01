<?php

namespace App\Http\Controllers;

use App\Models\Departamento;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Str;
use Carbon\Carbon;

class DepartamentoController extends Controller
{
    public function index()
    {
        return view('admin.departamentos.index');
    }

    public function store(Request $request)
    {
        $validator = \Validator::make($request->all(), [
            'nombre'=>'required|string|unique:departamentos',
            'imagen'=>'required|image',
        ], [
            'nombre.required'=>'El nombre del departamento es requerido.',
            'nombre.string'=>'Los valores ingresaodos no son admitidos.',
            'nombre.unique'=>'Ya existe un departamento con este nombre.',

            'imagen.required'=>'La imagen del departamento es requerida.',
            'imagen.image'=>'Archivos permitidos solo imagenes.',
        ]);

        if (!$validator->passes()) {
            return response()->json(['code'=>0, 'error'=>$validator->errors()->toArray()]);
        } else {
            $path = 'upload/';
            $file = $request->file('imagen');
            $extension = $request->file('imagen')->extension();
            $file_name = time().'_'.uniqid().'.'.$extension;

            $upload = $file->storeAs($path, $file_name);

            if($upload) {
                DB::table('departamentos')->insert([
                    'nombre'=>$request->nombre,
                    'slug'=>Str::slug($request->nombre, '_'),
                    'imagen'=>$file_name,
                    'created_at'=>Carbon::now('America/El_Salvador'),
                    'updated_at'=>Carbon::now('America/El_Salvador'),
                ]);

                return response()->json(['code'=>1, 'msg'=>'Departamento registrado correctamente']);
            }
        }   
    }

    public function getDepartamentos(Request $request) {
        $departamentos = Departamento::orderBy('id', 'DESC')->orWhere('nombre', 'LIKE', '%'.$request->search.'%')->paginate(10);
        $data = view('partials.admin.departamentos.getDepartamentos', compact('departamentos'))->render();
        return response()->json(['code'=>1, 'result'=>$data, 'links'=>$departamentos->links()->render()]);
    }

    public function deleteDepartamento(Request $request) {
        $departamento = Departamento::find($request->departamento_id);

        if ($departamento->imagen != null && \Storage::disk('local')->exists('upload/'.$departamento->imagen)) {
            \Storage::disk('local')->delete('app', 'upload/'.$departamento->imagen);
        }

        $delete = $departamento->delete();

        if($delete) {
            return response()->json(['code'=>1, 'msg'=>'Departamento eliminado correctamente']);
        } else {
            return response()->json(['code'=>0, 'msg'=>'Error al eliminar']);
        }
    }
}
